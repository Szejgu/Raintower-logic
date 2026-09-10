//#ifdef TEST

#include "unity.h"

#include "TaskSchedulerMain.h"
#include "TimeStructCalc.h"
#include "TS_TimeStruct_t.h"
#include "TaskScheduler_goodInit.h"
#include <stddef.h>
#include <string.h>


void setUp(void)
{
    HWTimestampGetCallCounter = 0;
    memset(&HWTimestampRet, 0, sizeof(TS_TimeStruct_t));
}

void tearDown(void)
{
}

void test_TaskScheduler_PlanAbsolute_module_not_initialised(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 16,
        .minute = 0,
        .second = 0,
        .milisecond = 0
        }
    };

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(UINT64_MAX, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_fixed_hour_upcoming(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 16,
        .minute = 0,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 15;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_TimeStruct_t TimeReturnExpected = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 0,
        .minute = 42,
        .second = 29,
        .milisecond = 758
        }
    };

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, HWTimestampGetCallCounter);
    TEST_ASSERT_EQUAL(TimeReturnExpected.raw, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_fixed_hour_next_day(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 16,
        .minute = 0,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 17;
    HWTimestampRet.data.minute = 17;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 242;

    TS_TimeStruct_t TimeReturnExpected = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 22,
        .minute = 42,
        .second = 29,
        .milisecond = 758
        }
    };

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, HWTimestampGetCallCounter);
    TEST_ASSERT_EQUAL(TimeReturnExpected.raw, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_plan_next_occurence_after_it_happened(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 16,
        .minute = 0,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 16;
    HWTimestampRet.data.minute = 0;
    HWTimestampRet.data.second = 0;
    HWTimestampRet.data.milisecond = 0;

    TS_TimeStruct_t TimeReturnExpected = {.data = {
        .year = 0,
        .day = 1,
        .month = 0,
        .hour = 0,
        .minute = 0,
        .second = 0,
        .milisecond = 0
        }
    };

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, HWTimestampGetCallCounter);
    TEST_ASSERT_EQUAL(TimeReturnExpected.raw, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_plan_next_fixed_hour_with_minutes(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 10,
        .minute = 30,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 9;
    HWTimestampRet.data.minute = 56;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 657;

    TS_TimeStruct_t TimeReturnExpected = {.data = {
        .year = 0,
        .day = 0,
        .month = 0,
        .hour = 0,
        .minute = 33,
        .second = 29,
        .milisecond = 342
        }
    };

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(1, HWTimestampGetCallCounter);
    TEST_ASSERT_EQUAL(TimeReturnExpected.raw, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_invalid_input_day(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 4,
        .month = 0,
        .hour = 10,
        .minute = 30,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 9;
    HWTimestampRet.data.minute = 56;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 657;

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(UINT64_MAX, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_invalid_input_month(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 4,
        .month = 2,
        .hour = 10,
        .minute = 30,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 9;
    HWTimestampRet.data.minute = 56;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 657;

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(UINT64_MAX, TimeReturnActual.raw);
    

}

void test_TaskScheduler_PlanAbsolute_invalid_input_year(void)
{
    //ARRANGE
    TS_TimeStruct_t TimeInput = {.data = {
        .year = 0,
        .day = 4,
        .month = 2,
        .hour = 10,
        .minute = 30,
        .second = 0,
        .milisecond = 0
        }
    };
    
    HWTimestampRet.data.year = 24;
    HWTimestampRet.data.day = 20;
    HWTimestampRet.data.month = 9;
    HWTimestampRet.data.hour = 9;
    HWTimestampRet.data.minute = 56;
    HWTimestampRet.data.second = 30;
    HWTimestampRet.data.milisecond = 657;

    TS_TimeStruct_t TimeReturnActual = {0};

    //ACT
    TS_InitStruct_t initStruct = goodInit();
    TS_InitErrorCodes_t result = TS_Init(&initStruct);

    TimeReturnActual = TS_PlanAbsolute(TimeInput);
 

    //ASSERT
    TEST_ASSERT_EQUAL(TS_InitErrorCodes_noError, result);
    TEST_ASSERT_EQUAL(UINT64_MAX, TimeReturnActual.raw);
    

}

//#endif // TEST
