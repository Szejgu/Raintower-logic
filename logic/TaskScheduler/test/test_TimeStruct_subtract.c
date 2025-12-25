#ifdef TEST

#include "unity.h"

#include "TS_TimeStruct_t.h"
#include "TimeStructCalc.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_TimeStruct_subtract_stub(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 15, .second = 0, .milisecond = 2, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 15, .second = 30, .milisecond = 498, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

#endif // TEST