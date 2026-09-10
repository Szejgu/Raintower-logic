#include "TaskScheduler_goodInit.h"
#include <string.h>


uint32_t HWTimestampGetCallCounter = 0;
TS_TimeStruct_t HWTimestampRet = {0};
TS_TimeStruct_t alarmSetValue = {0}; 

TS_TimeStruct_t SamplecurrTimeTabInst[TASK_LIST_LENGTH] = {0};

TaskDescriptor_t SampleTaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[2]}
    };
size_t SampleTaskListTab_size = TASK_LIST_LENGTH;

TS_InitStruct_t goodInit(void)
{
    TS_InitStruct_t ret = {0};

    ret.TaskListTab = SampleTaskList;
    ret.TaskListTab_size = SampleTaskListTab_size;
    ret.updateCurrentTimeFromHW = dummy_getHWTimestamp;
    ret.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct_t;
    ret.setNextWakeup = dummy_setNextAlarm;
    ret.setOrRestartTaskBreaker = dummy_setNextTaskBreaker;
    ret.resetTaskBreaker = dummy_resetTaskbreaker;

    return ret;
}


void dummy_getHWTimestamp(TS_TimeStruct_t* input)
{
    HWTimestampGetCallCounter++;
    memcpy(input, &HWTimestampRet, sizeof(TS_TimeStruct_t));
}

bool dummy_setNextAlarm(const TS_TimeStruct_t* input)
{
    memcpy(&alarmSetValue, input, sizeof(TS_TimeStruct_t));
    return true;
}

bool dummy_setNextTaskBreaker(const TS_TimeStruct_t* input)
{
    (void)input;
    return true;
}

bool dummy_resetTaskbreaker(void)
{
    return true;
}


TS_TimeStruct_t dummy_planNext(void)
{
    TS_TimeStruct_t ret = {0};
    return ret;
}

void dummy_fun(void)
{

}

bool b_dummy_const_TS_TimeStruct_t(const TS_TimeStruct_t* input)
{
    (void)input;
    return true;
}

void v_dummy_TS_TimeStruct_t(TS_TimeStruct_t* input)
{
    (void)input;
}


bool b_dummy_v(void)
{
    return true;
}
