//#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"
#include "TS_TimeStruct_t.h"
#include <string.h>

#define TASK_LIST_LENGTH 3
#define TASK_ORDER_TAB_LENGTH 10

#define DUMMY_TASK_MAX_EXEC_TIME { \
    .data = {\
        .year = 0, \
        .month = 0, \
        .day = 0, \
        .hour = 0, \
        .minute = 0, \
        .second = 1, \
        .milisecond = 0 \
    }\
}

#define DUMMY_TASK_MAX_EXEC_TIME2 { \
    .data = {\
        .year = 0, \
        .month = 0, \
        .day = 0, \
        .hour = 0, \
        .minute = 0, \
        .second = 0, \
        .milisecond = 900 \
    }\
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
static uint32_t TaskOrderTab[TASK_ORDER_TAB_LENGTH];
static uint32_t TaskOrderTab_index = 0;

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
    memset(TaskOrderTab, 0x0, TASK_ORDER_TAB_LENGTH*sizeof(uint32_t));
    TaskOrderTab_index = 0;
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

    task1_planNextRetVal.data.minute = 1;

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    input.TaskListTab_size = TaskSizeAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(20, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(15, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(18, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(30, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

}

void test_TaskScheduler_run_single_task_next_occurence_updated(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
    TaskDescriptor_t TaskListAlt[1] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    input.TaskListTab_size = TaskSizeAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 45;
    HWTimestampRet.data.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(20, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(15, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(18, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(30, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

}

void test_TaskScheduler_run_single_task_triggered_and_updated(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
    TaskDescriptor_t TaskListAlt[1] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    input.TaskListTab_size = TaskSizeAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 18;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(19, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(20, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(15, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(19, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(30, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

}

void test_TaskScheduler_run_single_task_overdue(void)
{
    //ARRANGE
    size_t TaskSizeAlt = 1;
    TS_TimeStruct_t task1_currTimeInst = {0};
    TaskDescriptor_t TaskListAlt[1] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    input.TaskListTab_size = TaskSizeAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.minute = 25;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(26, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(20, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(15, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(26, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(30, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);
    
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

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.second = 30;
    task3_planNextRetVal.data.hour = 12;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

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
    
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task2_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task2_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(0, task2_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task3_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(21, task3_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(17, task3_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(20, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(15, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(18, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(0, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

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

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.second = 30;
    task3_planNextRetVal.data.hour = 12;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();


    HWTimestampRet.data.minute = 18;
    HWTimestampRet.data.second = 0;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(0, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(0, task3_callCounter);
    
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(19, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task2_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(20, task2_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task2_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task3_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(21, task3_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task3_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(21, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(3, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(18, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(30, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

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

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.second = 30;
    task3_planNextRetVal.data.hour = 12;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.day = 22;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);
    
    TEST_ASSERT_EQUAL(24, task1_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task1_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(22, task1_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task1_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task1_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task1_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task1_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task2_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task2_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(22, task2_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(15, task2_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(18, task2_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(0, task2_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task2_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, task3_currTimeInst.data.year);
    TEST_ASSERT_EQUAL(9, task3_currTimeInst.data.month);
    TEST_ASSERT_EQUAL(23, task3_currTimeInst.data.day);
    TEST_ASSERT_EQUAL(3, task3_currTimeInst.data.hour);
    TEST_ASSERT_EQUAL(17, task3_currTimeInst.data.minute);
    TEST_ASSERT_EQUAL(30, task3_currTimeInst.data.second);
    TEST_ASSERT_EQUAL(242, task3_currTimeInst.data.milisecond);

    TEST_ASSERT_EQUAL(24, alarmSetValue.data.year);
    TEST_ASSERT_EQUAL(9, alarmSetValue.data.month);
    TEST_ASSERT_EQUAL(22, alarmSetValue.data.day);
    TEST_ASSERT_EQUAL(3, alarmSetValue.data.hour);
    TEST_ASSERT_EQUAL(18, alarmSetValue.data.minute);
    TEST_ASSERT_EQUAL(0, alarmSetValue.data.second);
    TEST_ASSERT_EQUAL(242, alarmSetValue.data.milisecond);

}

void test_TaskScheduler_run_multiple_tasks_properly_preemtied(void)
{
        //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_low,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_high,DUMMY_TASK_MAX_EXEC_TIME, &task3_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.minute = 1;
    task3_planNextRetVal.data.minute = 1;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 22;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 18;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);
    
    TEST_ASSERT_EQUAL(3, TaskOrderTab[0]);
    TEST_ASSERT_EQUAL(2, TaskOrderTab[1]);
    TEST_ASSERT_EQUAL(1, TaskOrderTab[2]);

}

void test_TaskScheduler_run_multiple_tasks_properly_preemtied_same_priority(void)
{
        //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_high,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_high,DUMMY_TASK_MAX_EXEC_TIME, &task3_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.minute = 1;
    task3_planNextRetVal.data.minute = 1;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 22;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 18;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);
    
    TEST_ASSERT_EQUAL(1, TaskOrderTab[0]);
    TEST_ASSERT_EQUAL(3, TaskOrderTab[1]);
    TEST_ASSERT_EQUAL(2, TaskOrderTab[2]);

}

void test_TaskScheduler_run_multiple_tasks_properly_preemtied_same_priority_different_max_time(void)
{
        //ARRANGE
    TS_TimeStruct_t task1_currTimeInst = {0};
    TS_TimeStruct_t task2_currTimeInst = {0};
    TS_TimeStruct_t task3_currTimeInst = {0};

    TaskDescriptor_t TaskListAlt[TASK_LIST_LENGTH] = {
        {dummy_task1, dummy_task1_planNext, TS_Priority_high,DUMMY_TASK_MAX_EXEC_TIME, &task1_currTimeInst},
        {dummy_task2, dummy_task2_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &task2_currTimeInst},
        {dummy_task3, dummy_task3_planNext, TS_Priority_high,DUMMY_TASK_MAX_EXEC_TIME2, &task3_currTimeInst}
    };

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.minute = 1;
    task3_planNextRetVal.data.minute = 1;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    TS_Run();

    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 22;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 18;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_Run();

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(1, task1_callCounter);
    TEST_ASSERT_EQUAL(1, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);
    
    TEST_ASSERT_EQUAL(3, TaskOrderTab[0]);
    TEST_ASSERT_EQUAL(1, TaskOrderTab[1]);
    TEST_ASSERT_EQUAL(2, TaskOrderTab[2]);

}

void test_TaskScheduler_run_multiple_tasks_chained_tasks(void)
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

    task1_planNextRetVal.data.minute = 1;
    task2_planNextRetVal.data.minute = 2;
    task3_planNextRetVal.data.minute = 4;


    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_InitStruct_t input = goodInit();
    input.TaskListTab = TaskListAlt;
    
    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);
    
    TS_Run();

    HWTimestampRet.data.minute = 18;

    TS_Run(); //T1

    HWTimestampRet.data.minute = 19;

    TS_Run(); //T1 T2

    HWTimestampRet.data.minute = 20;

    TS_Run(); // T1

    HWTimestampRet.data.minute = 21;

    TS_Run(); // T1 T2 T3

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    
    TEST_ASSERT_EQUAL(4, task1_callCounter);
    TEST_ASSERT_EQUAL(2, task2_callCounter);
    TEST_ASSERT_EQUAL(1, task3_callCounter);

    TEST_ASSERT_EQUAL(1, TaskOrderTab[0]);
    TEST_ASSERT_EQUAL(1, TaskOrderTab[1]);
    TEST_ASSERT_EQUAL(2, TaskOrderTab[2]);
    TEST_ASSERT_EQUAL(1, TaskOrderTab[3]);
    TEST_ASSERT_EQUAL(1, TaskOrderTab[4]);
    TEST_ASSERT_EQUAL(2, TaskOrderTab[5]);
    TEST_ASSERT_EQUAL(3, TaskOrderTab[6]);

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
    TaskOrderTab[TaskOrderTab_index] = 1;
    TaskOrderTab_index++;
}

static void dummy_task2(void)
{
    task2_callCounter++;
    TaskOrderTab[TaskOrderTab_index] = 2;
    TaskOrderTab_index++;
}

static void dummy_task3(void)
{
    task3_callCounter++;
    TaskOrderTab[TaskOrderTab_index] = 3;
    TaskOrderTab_index++;
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
//#endif // TEST
