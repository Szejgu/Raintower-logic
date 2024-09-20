#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"
#include <string.h>

#define TASK_LIST_LENGTH 3
#define DUMMY_TASK_MAX_EXEC_TIME { \
    .year = 0, \
    .month = 0, \
    .day = 0, \
    .hour = 0, \
    .minute = 0, \
    .second = 1, \
    .milisecond = 0 \
}

static void dummy_fun(void);
static TS_TimeStruct dummy_planNext(void);
static void dummy_getHWTimestamp(TS_TimeStruct* input);
static bool b_dummy_const_TS_TimeStruct(const TS_TimeStruct* input);
static bool dummy_setNextAlarm(const TS_TimeStruct* input);
static bool dummy_setNextTaskBreaker(const TS_TimeStruct* input);
static bool dummy_resetTaskbreaker(void);
static TS_InitStruct_t goodInit(void);

static void dummy_task1(void);
static TS_TimeStruct dummy_task1_planNext(void);

static TS_TimeStruct HWTimestampRet = {0};
static uint32_t HWTimestampGetCallCounter = 0;
static uint32_t task1_callCounter = 0;
static TS_TimeStruct task1_planNextRetVal = {0};

static TS_TimeStruct SamplecurrTimeTabInst[TASK_LIST_LENGTH] = {0};
TaskDescriptor_t SampleTaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &SamplecurrTimeTabInst[2]}
    };
size_t SampleTaskListTab_size = TASK_LIST_LENGTH;

void setUp(void)
{
    HWTimestampGetCallCounter = 0;
    task1_callCounter = 0;
    memset(&task1_planNextRetVal, 0x00, sizeof(TS_TimeStruct));
}

void tearDown(void)
{
}

void test_TaskScheduler_run_not_executed_without_init(void)
{
    //ARRANGE
    
    //ACT
    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(0, HWTimestampGetCallCounter);

}

void test_TaskScheduler_run_single_task_next_occurence_updated(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct task1_currTimeInst = {0};
    TaskDescriptor_t TaskListAlt[1] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst}
    };

    task1_planNextRetVal.minute = 1;

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 17;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    input.TaskListTab_size = TaskSizeAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

}

static TS_InitStruct_t goodInit(void)
{
    TS_InitStruct_t ret = {0};

    ret.TaskListTab = SampleTaskList;
    ret.TaskListTab_size = SampleTaskListTab_size;
    ret.updateCurrentTimeFromHW = dummy_getHWTimestamp;
    ret.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct;
    ret.setNextWakeup = dummy_setNextAlarm;
    ret.setOrRestartTaskBreaker = dummy_setNextTaskBreaker;
    ret.resetTaskBreaker = dummy_resetTaskbreaker;

    return ret;
}

static void dummy_fun(void)
{

}

static TS_TimeStruct dummy_planNext(void)
{
    TS_TimeStruct ret = {0};
    return ret;
}

static void dummy_getHWTimestamp(TS_TimeStruct* input)
{
    HWTimestampGetCallCounter++;
    memcpy(input, &HWTimestampRet, sizeof(TS_TimeStruct));
}

static bool b_dummy_const_TS_TimeStruct(const TS_TimeStruct* input)
{
    (void)input;
    return true;
}

static bool dummy_resetTaskbreaker(void)
{
    return true;
}

static bool dummy_setNextAlarm(const TS_TimeStruct* input)
{
    (void)input;
    return true;
}

static bool dummy_setNextTaskBreaker(const TS_TimeStruct* input)
{
    (void)input;
    return true;
}

static void dummy_task1(void)
{
    
}

static TS_TimeStruct dummy_task1_planNext(void)
{

}

#endif // TEST
