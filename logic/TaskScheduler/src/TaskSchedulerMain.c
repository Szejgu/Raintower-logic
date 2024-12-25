#include "TaskSchedulerMain.h"
#include "TimeStructCalc.h"

#define TASK_INDEX_NOT_PLANNED 0xFFFFFFFFU
#define MINIMUM_TIME_EXECUTION_MARGIN 5U
#define MAX_NUMBER_OF_TASKS 10

static const TS_TimeStruct_t MaximumExecTimeInst = TASK_LIMIT_STRUCT;

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

static void updateNextTaskIndex(void);
static void updateTimeToNextInst(void);
static bool isNextTaskImmidiate(void);

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
    */
   if(!moduleInitState)
   {
        return;
   }

   updateTimeToNextInst();

   updateNextTaskIndex();

    if(isNextTaskImmidiate())
    {

    }
    else
    {
        setNextWakeup_local(TaskListTab_local[index_of_task_to_execute_next].TimeToNextInst);
    }

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

    for(uint32_t i = 1; i < TaskListTab_size_local; i++)
    {
        if(TaskListTab_local[nextTaskIndex_local].TimeToNextInst->raw > TaskListTab_local[i].TimeToNextInst->raw )
        {
            nextTaskIndex_local = i;
        }       
    }

    uint32_t numPreemptions = 0, preemptionTabIter = 0;
    uint32_t preemptionTab[MAX_NUMBER_OF_TASKS] = {0};

    TS_TimeStruct_t dateToCheckPreemptions = TimeStruct_add(*(TaskListTab_local[nextTaskIndex_local].TimeToNextInst), TaskListTab_local[nextTaskIndex_local].MaximumExecTime);

    for(uint32_t i = 0; i < TaskListTab_size_local; i++)
    {
        if(i == nextTaskIndex_local)
        {
            continue;
        }

        if(dateToCheckPreemptions.raw > TaskListTab_local[i].TimeToNextInst->raw )
        {
            numPreemptions++;
            preemptionTab[preemptionTabIter] = i;
            preemptionTabIter++;
        }       
    }

    if(0 == numPreemptions)
    {
       index_of_task_to_execute_next = nextTaskIndex_local;
    }
    else
    {
        /* ogarnać wywłaszczenia, bo wiem ile ich jest i które to są*/
    }

}

static void updateTimeToNextInst(void)
{
    TS_TimeStruct_t now = {0};
    updateCurrentTimeFromHW_local(&now);

    for(uint32_t i = 0; i < TaskListTab_size_local; i++)
    {
        *(TaskListTab_local[i].TimeToNextInst) = TimeStruct_add(now, TaskListTab_local[i].PlanNextInst());
    }
}

static bool isNextTaskImmidiate(void)
{
    bool ret = false;



    return ret;
}