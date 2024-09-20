#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_TaskScheduler_Init_TaskTab_NULL(void)
{
    //ARRANGE
    TS_InitStruct_t input = {0};

    //ACT
    TS_InitErrorCodes_t result = TS_Init(&input);

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_TaskList_NULL, result);

}

#endif // TEST
