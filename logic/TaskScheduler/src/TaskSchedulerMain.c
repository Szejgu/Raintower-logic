#include "TaskSchedulerMain.h"

static const TS_TimeStruct_t MaximumExecTimeInst = TASK_LIMIT_STRUCT;

static   TaskDescriptor_t* TaskListTab_local = NULL;
static   size_t TaskListTab_size_local = 0;

static   void (*updateCurrentTimeFromHW_local)(TS_TimeStruct_t* input) = NULL;
static   bool (*setCurrentTimeInHW_local)(const TS_TimeStruct_t* input) = NULL;

static   bool (*setNextWakeup_local)(const TS_TimeStruct_t* input) = NULL;

static   bool (*setOrRestartTaskBreaker_local)(const TS_TimeStruct_t* input) = NULL;
static   bool (*resetTaskBreaker_local)(void) = NULL;

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

        retVal = TS_InitErrorCodes_noError;
    }

    return retVal;
}

void TS_UpdateWakeupStatus(bool status)
{
    (void)status;   
}

void TS_Run(void)
{

}

TS_TimeStruct_t TS_PlanAbsolute(TS_TimeStruct_t date)
{
    TS_TimeStruct_t ret = {0};

    return ret;
}

bool TS_DidTimeoutOccur(void)
{
    return true;
}