#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"
#include "TimeStructCalc.h"
#include "TS_TimeStruct_t.h"
#include "TaskScheduler_goodInit.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_TaskScheduler_Init_TaskList_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_NULL, result);

}

void test_TaskScheduler_Init_TaskList_Integrity_error_no_func_ptrs(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {0};
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_Integrity_error, result);
}

void test_TaskScheduler_Init_TaskList_Integrity_error_no_timeToNextInst(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, NULL},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, NULL},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, NULL}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_Integrity_error, result);
}

void test_TaskScheduler_Init_TaskList_Integrity_error_maximumExecTimeZero(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,TASK_MAX_EXEC_TIME_ALL_ZERO, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_Integrity_error, result);
}

void test_TaskScheduler_Init_TaskList_Integrity_error_maximumExecTooHigh(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TS_TimeStruct_t MaxTaskTime = TASK_LIMIT_STRUCT;
    MaxTaskTime.data.year += 1;

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,MaxTaskTime, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_Integrity_error, result);
}

void test_TaskScheduler_Init_updateCurrentTimeFromHW_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_updateCurrentTimeFromHW_NULL, result);
}

void test_TaskScheduler_Init_setCurrentTimeInHW_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;
    input.updateCurrentTimeFromHW = v_dummy_TS_TimeStruct_t;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_setCurrentTimeInHW_NULL, result);
}

void test_TaskScheduler_Init_setNextWakeup_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;
    input.updateCurrentTimeFromHW = v_dummy_TS_TimeStruct_t;
    input.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct_t;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_setNextWakeup_NULL, result);
}

void test_TaskScheduler_Init_setOrRestartTaskBreaker_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;
    input.updateCurrentTimeFromHW = v_dummy_TS_TimeStruct_t;
    input.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct_t;
    input.setNextWakeup = b_dummy_const_TS_TimeStruct_t;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_setOrRestartTaskBreaker_NULL, result);
}

void test_TaskScheduler_Init_resetTaskBreaker_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;
    input.updateCurrentTimeFromHW = v_dummy_TS_TimeStruct_t;
    input.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct_t;
    input.setNextWakeup = b_dummy_const_TS_TimeStruct_t;
    input.setOrRestartTaskBreaker = b_dummy_const_TS_TimeStruct_t;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_resetTaskBreaker_NULL, result);
}

void test_TaskScheduler_Init_happy_path(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};
    TS_TimeStruct_t currTimeTabInst[TASK_LIST_LENGTH] = {0};

    TaskDescriptor_t TaskList[TASK_LIST_LENGTH] = {
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[0]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[1]},
        {dummy_fun, dummy_planNext, TS_Priority_normal,DUMMY_TASK_MAX_EXEC_TIME, &currTimeTabInst[2]}
    };
    input.TaskListTab = TaskList;
    input.TaskListTab_size = TASK_LIST_LENGTH;
    input.updateCurrentTimeFromHW = v_dummy_TS_TimeStruct_t;
    input.setCurrentTimeInHW = b_dummy_const_TS_TimeStruct_t;
    input.setNextWakeup = b_dummy_const_TS_TimeStruct_t;
    input.setOrRestartTaskBreaker = b_dummy_const_TS_TimeStruct_t;
    input.resetTaskBreaker = b_dummy_v;

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
}


#endif // TEST
