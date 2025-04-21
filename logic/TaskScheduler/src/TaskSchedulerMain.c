#include "TaskSchedulerMain.h"
#include "TimeStructCalc.h"

#define TASK_INDEX_NOT_PLANNED 0xFFFFFFFFU
#define MINIMUM_TIME_EXECUTION_MARGIN 5U
#define MAX_NUMBER_OF_TASKS 10 //TODO: check this in init
#define MARGIN_FOR_IMMIDIATE_TASK_EXECUTION_MS 20

static const TS_TimeStruct_t MaximumExecTimeInst = TASK_LIMIT_STRUCT;
static TS_TimeStruct_t now = {0};

static   TaskDescriptor_t* TaskListTab_local = NULL;
static   size_t TaskListTab_size_local = 0;

static   void (*updateCurrentTimeFromHW_local)(TS_TimeStruct_t* input) = NULL;
static   bool (*setCurrentTimeInHW_local)(const TS_TimeStruct_t* input) = NULL;

static   bool (*setNextWakeup_local)(const TS_TimeStruct_t* input) = NULL;

static   bool (*setOrRestartTaskBreaker_local)(const TS_TimeStruct_t* input) = NULL;
static   bool (*resetTaskBreaker_local)(void) = NULL;

static uint32_t index_of_task_to_execute_next = TASK_INDEX_NOT_PLANNED;

static bool wakeup_from_RTC_IRQ = false;
static bool moduleInitState = false;
static bool TaskListNeedsUpdating = false;
static bool taskOverdue = false;
static uint32_t numOverdueTasks_local = 0;
static uint32_t maxPreemptions = 0;
static bool preemptionsUpdated = false;


static void updateNextTaskIndex(void);
static void updateTimeToNextInstAll(void);
static void updateTimeToNextInst(uint32_t index);
static bool isNextTaskImmidiate(void);
static bool isTaskOverdue(uint32_t* numOverdueTasks);


TS_InitErrorCodes_t TS_Init(TS_InitStruct_t* input)
{
    TS_InitErrorCodes_t retVal = TS_InitErrorCodes_unknownError;

    do{

        if(NULL == input->TaskListTab)
        {
            retVal = TS_InitErrorCodes_TaskList_NULL;
            break;
        }

        for(uint8_t i = 0; i < input->TaskListTab_size; i++)
        {
            if(NULL == input->TaskListTab[i].TimeToNextInst || NULL == input->TaskListTab[i].TaskFunPtr || NULL == input->TaskListTab[i].PlanNextInst)
            {
                retVal = TS_InitErrorCodes_TaskList_Integrity_error;
                break;
            }

            if(input->TaskListTab[i].MaximumExecTime.raw > MaximumExecTimeInst.raw || 0 == input->TaskListTab[i].MaximumExecTime.raw)
            {
                retVal = TS_InitErrorCodes_TaskList_Integrity_error;
                break;
            }
        }

        if(TS_InitErrorCodes_unknownError != retVal)
        {
            break;
        }

        if(NULL == input->updateCurrentTimeFromHW)
        {
            retVal = TS_InitErrorCodes_updateCurrentTimeFromHW_NULL;
            break;
        }

        if(NULL == input->setCurrentTimeInHW)
        {
            retVal = TS_InitErrorCodes_setCurrentTimeInHW_NULL;
            break;
        }

        if(NULL == input->setNextWakeup)
        {
            retVal = TS_InitErrorCodes_setNextWakeup_NULL;
            break;
        }

        if(NULL == input->setOrRestartTaskBreaker)
        {
            retVal = TS_InitErrorCodes_setOrRestartTaskBreaker_NULL;
            break;
        }

        if(NULL == input->resetTaskBreaker)
        {
            retVal = TS_InitErrorCodes_resetTaskBreaker_NULL;
            break;
        }

    }while(false);

    if(TS_InitErrorCodes_unknownError == retVal)
    {
        TaskListTab_local = input->TaskListTab;
        TaskListTab_size_local = input->TaskListTab_size;
        updateCurrentTimeFromHW_local = input->updateCurrentTimeFromHW;
        setCurrentTimeInHW_local = input->setCurrentTimeInHW;
        setNextWakeup_local = input->setNextWakeup;
        setOrRestartTaskBreaker_local = input->setOrRestartTaskBreaker;
        resetTaskBreaker_local = input->resetTaskBreaker;

        moduleInitState = true;
        retVal = TS_InitErrorCodes_noError;
        TaskListNeedsUpdating = true;
    }

    return retVal;
}

void TS_UpdateWakeupStatus(bool status)
{
    wakeup_from_RTC_IRQ = status;
}

void TS_Run(void)
{
    /*
    To jest funkcja która odpala się potencjalnie przy każdym przerwaniu, niezależnie od źródła
    A więc musi robić takie rzeczy:
    1. obejrzeć czy czasem nie ma czegoś do odpalenia teraz - czy to przez fakt że jest na to czas, czy to przez jakieś inne źródło
    2. odpalić takie "natychmiastowe" zadanie - przed odpaleniem ustawić przerwanie od Task Breakera i włączyć zadanie
    2.1 po odpaleniu wyłaczyć taks breaker
    3. przeliczyć kolejkę reszty zadań
    4. wybrać odpowiednio kolejne zadanie - z uwzględnieniem priorytetów i maksymalnego czasu wykonywania
    4.1 jak trzeba odpalić kolejne to odpalić, wraz z zachowaniem task breakera
    4.2 w przypadku gdy nie trzeba to przejść dalej
    5. ustawić odpowiednie przerwanie od RTC


    notatki dalej:

    - planowanie kolejnych instancji zadania powinno dziać się względem czasu startu, nie zakończenia zadania
    - kolejność w arbitrażu wywłaszczania to priorytet -> najkrótszy max.exec.time -> kolejność na liście
    - w każdym innym przypadku o kolejności decyduje najbliższe zadanie
    - wywłaszczenie występuje wtedy, kiedy początek zadania plus max.exec.time nachodzi na początek innego zadania
    - w przypadku, gdy zaśpimy, zadania które miały się w tym czasie wykonać wykonują się raz
    - w takim też przypadku następne instancje są planowane względem czasu wybudzenia

    */
    if(!moduleInitState)
    {
        return;
    }

    updateCurrentTimeFromHW_local(&now);

    if(TaskListNeedsUpdating)
    {
        updateTimeToNextInstAll();
        TaskListNeedsUpdating = false;
    }

    numOverdueTasks_local = 0;
    maxPreemptions = 0;
    preemptionsUpdated = false;
    taskOverdue = isTaskOverdue(&numOverdueTasks_local);


    
    do{
        updateNextTaskIndex();

        if(isNextTaskImmidiate())
        {

            TaskListTab_local[index_of_task_to_execute_next].TaskFunPtr();
            updateTimeToNextInst(index_of_task_to_execute_next);
            setNextWakeup_local(TaskListTab_local[index_of_task_to_execute_next].TimeToNextInst);

        }
        else
        {
            setNextWakeup_local(TaskListTab_local[index_of_task_to_execute_next].TimeToNextInst);
        }

        if(0 < numOverdueTasks_local)
        {
            //updateCurrentTimeFromHW_local(&now);
            numOverdueTasks_local--;
        }
        else
        {
            taskOverdue = false;
        }

        
        if(maxPreemptions > 0)
        {
            maxPreemptions--;
        }
        

    }
    while(taskOverdue || maxPreemptions > 0);
}

TS_TimeStruct_t TS_PlanAbsolute(TS_TimeStruct_t date)
{
    TS_TimeStruct_t ret = {0};
    (void)date;

    return ret;
}

bool TS_DidTimeoutOccur(void)
{
    return true;
}

static void updateNextTaskIndex(void)
{
    uint32_t nextTaskIndex_local = 0;
    TS_TimeStruct_t closestNextTask = *TaskListTab_local[0].TimeToNextInst;
    uint32_t timesPreemptied = 0;

    for(uint32_t i = 1; i < TaskListTab_size_local; i++)
    {
        if(closestNextTask.raw > TaskListTab_local[i].TimeToNextInst->raw )
        {
            closestNextTask = *TaskListTab_local[i].TimeToNextInst;
            nextTaskIndex_local = i;
        }
    }

    for(uint32_t j = 0; j < TaskListTab_size_local; j++)
    {
        if(TaskListTab_local[j].Priority >= TaskListTab_local[nextTaskIndex_local].Priority )
        {
            if((TimeStruct_add(closestNextTask, TaskListTab_local[nextTaskIndex_local].MaximumExecTime)).raw >= TaskListTab_local[j].TimeToNextInst->raw)
            {
                nextTaskIndex_local = j;
                closestNextTask = *TaskListTab_local[j].TimeToNextInst;
                timesPreemptied++;
            }
        }
    }


    if(!preemptionsUpdated)
    {
        maxPreemptions = timesPreemptied + 1; //because of the nature of do-while loop
        preemptionsUpdated = true;
    }

    index_of_task_to_execute_next = nextTaskIndex_local;

}

static void updateTimeToNextInstAll(void)
{  
    for(uint32_t i = 0; i < TaskListTab_size_local; i++)
    {
        *(TaskListTab_local[i].TimeToNextInst) = TimeStruct_add(now, TaskListTab_local[i].PlanNextInst());
    }
}

static bool isNextTaskImmidiate(void)
{
    bool ret = false;
    TS_TimeStruct_t margin = {0};
    margin.data.milisecond = MARGIN_FOR_IMMIDIATE_TASK_EXECUTION_MS;

    TS_TimeStruct_t nowWithMargin = TimeStruct_add(now, margin);

    if(nowWithMargin.raw >= TaskListTab_local[index_of_task_to_execute_next].TimeToNextInst->raw)
    {
        ret = true;
    }

    return ret;
}

static void updateTimeToNextInst(uint32_t index)
{
    *(TaskListTab_local[index].TimeToNextInst) = TimeStruct_add(now, TaskListTab_local[index].PlanNextInst());
}

static bool isTaskOverdue(uint32_t* numOverdueTasks)
{
    bool ret = false;

    *numOverdueTasks = 0;

    for(uint32_t i = 0; i < TaskListTab_size_local; i++)
    {
        if(TaskListTab_local[i].TimeToNextInst->raw < now.raw )
        {
            *numOverdueTasks+=1;
        }
    }

    if(0 != numOverdueTasks)
    {
        ret = true;
    }

    return ret;
}
