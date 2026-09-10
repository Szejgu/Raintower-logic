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

void test_TimeStruct_subtract_miliseconds_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 0, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_miliseconds_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 0, .milisecond = 750, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 29, .milisecond = 750, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}


void test_TimeStruct_subtract_seconds_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_seconds_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 50, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 29, .second = 40, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_minutes_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_minutes_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 45, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 14, .minute = 45, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_hours_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 15, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_hours_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 20, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 4, .day = 14, .hour = 19, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_days_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 3, .day = 31, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_days_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 20, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 25, .month = 3, .day = 26, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_months_p1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 24, .month = 11, .day = 30, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_months_p2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 6, .day = 20, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 24, .month = 9, .day = 26, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_years_resulting_leap(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 25, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 1, .month = 1, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 24, .month = 2, .day = 29, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStruct_subtract_years_resulting_non_leap(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 24, .month = 4, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t b = {.data = {.year = 1, .month = 1, .day = 15, .hour = 15, .minute = 30, .second = 30, .milisecond = 500, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};
    TS_TimeStruct_t expected_result = {.data = {.year = 23, .month = 2, .day = 28, .hour = 0, .minute = 0, .second = 0, .milisecond = 0, .hour_overflow = 0, .day_overflow = 0, .month_overflow = 0, .unused = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_subtract(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

#endif // TEST