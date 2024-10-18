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

void test_TimeStructCalc_add_roll_over_to_seconds_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0, .milisecond = 500}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 0, .milisecond = 500}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 1, .milisecond = 0}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_seconds_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0, .milisecond = 750}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 0, .milisecond = 500}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 1, .milisecond = 250}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_minutes_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 30, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 30, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 1, .second = 0, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_minutes_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 45, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 0, .second = 30, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 1, .second = 15, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_hours_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 30, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 30, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 1, .minute = 0, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_hours_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 0, .minute = 45, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 0, .minute = 30, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 1, .hour = 1, .minute = 15, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_days_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 12, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 12, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 2, .hour = 0, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_days_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 1, .hour = 12, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 0, .hour = 18, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 1, .day = 2, .hour = 6, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 12, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 2, .day = 1, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 2, .day = 9, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part3(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 4, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 5, .day = 10, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part4(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 4, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 12, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 5, .day = 2, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part5(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 1, .day = 31, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 1, .day = 0, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 2, .day = 29, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_part6(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 1, .month = 1, .day = 31, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 1, .day = 0, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 1, .month = 2, .day = 28, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_febuary_in_leap_year(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 2, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 0, .month = 3, .day = 11, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_months_febuary_in_non_leap_year(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 1, .month = 2, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 0, .day = 20, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 1, .month = 3, .day = 12, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_years_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 6, .day = 10, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 7, .day = 10, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 1, .month = 1, .day = 20, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

void test_TimeStructCalc_add_roll_over_to_years_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {.data = {.year = 0, .month = 6, .day = 10, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t b = {.data = {.year = 0, .month = 10, .day = 10, .hour = 10, .minute = 10, .second = 10, .milisecond = 100}};
    TS_TimeStruct_t expected_result = {.data = {.year = 1, .month = 4, .day = 20, .hour = 20, .minute = 20, .second = 20, .milisecond = 200}};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL(expected_result.raw, result.raw);

}

#endif // TEST