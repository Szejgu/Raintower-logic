#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"
#include "TS_TimeStruct_t.h"
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
static TS_TimeStruct_t dummy_planNext(void);
static void dummy_getHWTimestamp(TS_TimeStruct_t* input);
static bool b_dummy_const_TS_TimeStruct_t(const TS_TimeStruct_t* input);
static bool dummy_setNextAlarm(const TS_TimeStruct_t* input);
static bool dummy_setNextTaskBreaker(const TS_TimeStruct_t* input);
static bool dummy_resetTaskbreaker(void);
static TS_InitStruct_t goodInit(void);

static void dummy_task1(void);
static TS_TimeStruct_t dummy_task1_planNext(void);

static void dummy_task2(void);
static TS_TimeStruct_t dummy_task2_planNext(void);

static void dummy_task3(void);
static TS_TimeStruct_t dummy_task3_planNext(void);

static TS_TimeStruct_t HWTimestampRet = {0};
static uint32_t HWTimestampGetCallCounter = 0;
static uint32_t task1_callCounter = 0;
static uint32_t task2_callCounter = 0;
static uint32_t task3_callCounter = 0;
static TS_TimeStruct_t task1_planNextRetVal = {0};
static TS_TimeStruct_t task2_planNextRetVal = {0};
static TS_TimeStruct_t task3_planNextRetVal = {0};
static TS_TimeStruct_t alarmSetValue = {0}; 

static TS_TimeStruct_t SamplecurrTimeTabInst[TASK_LIST_LENGTH] = {0};
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
    task2_callCounter = 0;
    task3_callCounter = 0;
    memset(&task1_planNextRetVal, 0x00, sizeof(TS_TimeStruct_t));
    memset(&task2_planNextRetVal, 0x00, sizeof(TS_TimeStruct_t));
    memset(&task3_planNextRetVal, 0x00, sizeof(TS_TimeStruct_t));
    memset(&alarmSetValue, 0x00, sizeof(TS_TimeStruct_t));
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

void test_TaskScheduler_run_single_task_next_occurence_updated_first_time(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
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

void test_TaskScheduler_run_single_task_next_occurence_updated(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
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

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 17;
    HWTimestampRet.second = 45;
    HWTimestampRet.milisecond = 242;

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

void test_TaskScheduler_run_single_task_triggered_and_updated(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
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

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 18;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(19, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

}

void test_TaskScheduler_run_single_task_overdue(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
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

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 25;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(26, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

}

void test_TaskScheduler_run_multiple_tasks_properly_assigned(void)
{
    //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task3_currTimeInst}
    };

    task1_planNextRetVal.minute = 1;
    task2_planNextRetVal.second = 30;
    task3_planNextRetVal.hour = 12;


    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 17;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(0, task1_callCounter);
    TEST_ASSERT_EQUAL(0, task2_callCounter);
    TEST_ASSERT_EQUAL(0, task3_callCounter);
    
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task2_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task2_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.minute);
    TEST_ASSERT_EQUAL(0, task2_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task3_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.month);
    TEST_ASSERT_EQUAL(21, task3_currTimeInst.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.hour);
    TEST_ASSERT_EQUAL(17, task3_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.milisecond);

}

void test_TaskScheduler_run_multiple_tasks_triggered_and_updated(void)
{
    //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task3_currTimeInst}
    };

    task1_planNextRetVal.minute = 1;
    task2_planNextRetVal.second = 30;
    task3_planNextRetVal.hour = 12;


    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 17;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 18;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(0, task2_callCounter);
    TEST_ASSERT_EQUAL(0, task3_callCounter);
    
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(19, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task2_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.month);
    TEST_ASSERT_EQUAL(20, task2_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.minute);
    TEST_ASSERT_EQUAL(0, task2_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task3_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.month);
    TEST_ASSERT_EQUAL(21, task3_currTimeInst.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.hour);
    TEST_ASSERT_EQUAL(17, task3_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.milisecond);

}

void test_TaskScheduler_run_multiple_tasks_overdue(void)
{
    //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task3_currTimeInst}
    };

    task1_planNextRetVal.minute = 1;
    task2_planNextRetVal.second = 30;
    task3_planNextRetVal.hour = 12;


    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 20;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 17;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.year = 2024;
    HWTimestampRet.day = 22;
    HWTimestampRet.month = 9;
    HWTimestampRet.hour = 15;
    HWTimestampRet.minute = 18;
    HWTimestampRet.second = 30;
    HWTimestampRet.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);
    
    TEST_ASSERT_EQUAL(2024, task1_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.month);
    TEST_ASSERT_EQUAL(22, task1_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.hour);
    TEST_ASSERT_EQUAL(19, task1_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task2_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.month);
    TEST_ASSERT_EQUAL(22, task2_currTimeInst.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.minute);
    TEST_ASSERT_EQUAL(0, task2_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.milisecond);

    TEST_ASSERT_EQUAL(2024, task3_currTimeInst.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.month);
    TEST_ASSERT_EQUAL(21, task3_currTimeInst.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.hour);
    TEST_ASSERT_EQUAL(17, task3_currTimeInst.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.milisecond);

}

static TS_InitStruct_t goodInit(void)
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

static void dummy_fun(void)
{

}

static TS_TimeStruct_t dummy_planNext(void)
{
    TS_TimeStruct_t ret = {0};
    return ret;
}

static void dummy_getHWTimestamp(TS_TimeStruct_t* input)
{
    HWTimestampGetCallCounter++;
    memcpy(input, &HWTimestampRet, sizeof(TS_TimeStruct_t));
}

static bool b_dummy_const_TS_TimeStruct_t(const TS_TimeStruct_t* input)
{
    (void)input;
    return true;
}

static bool dummy_resetTaskbreaker(void)
{
    return true;
}

static bool dummy_setNextAlarm(const TS_TimeStruct_t* input)
{
    memcpy(&alarmSetValue, input, sizeof(TS_TimeStruct_t));
    return true;
}

static bool dummy_setNextTaskBreaker(const TS_TimeStruct_t* input)
{
    (void)input;
    return true;
}

static void dummy_task1(void)
{
    task1_callCounter++;
}

static void dummy_task2(void)
{
    task2_callCounter++;
}

static void dummy_task3(void)
{
    task3_callCounter++;
}

static TS_TimeStruct_t dummy_task1_planNext(void)
{
    return task1_planNextRetVal;
}

static TS_TimeStruct_t dummy_task2_planNext(void)
{
    return task2_planNextRetVal;
}
static TS_TimeStruct_t dummy_task3_planNext(void)
{
    return task3_planNextRetVal;
}
#endif // TEST
