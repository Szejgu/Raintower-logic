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
    TS_TimeStruct_t a = {0,1,0,0,0,0,500};
    TS_TimeStruct_t b = {0,0,0,0,0,0,500};
    TS_TimeStruct_t expected_result = {0,1,0,0,0,1,0};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_seconds_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,0,0,0,750};
    TS_TimeStruct_t b = {0,0,0,0,0,0,500};
    TS_TimeStruct_t expected_result = {0,1,0,0,0,1,250};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_minutes_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,0,0,30,100};
    TS_TimeStruct_t b = {0,0,0,0,0,30,100};
    TS_TimeStruct_t expected_result = {0,1,0,0,1,0,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_minutes_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,0,0,45,100};
    TS_TimeStruct_t b = {0,0,0,0,0,30,100};
    TS_TimeStruct_t expected_result = {0,1,0,0,1,15,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_hours_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,0,30,10,100};
    TS_TimeStruct_t b = {0,0,0,0,30,10,100};
    TS_TimeStruct_t expected_result = {0,1,0,1,0,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_hours_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,0,45,10,100};
    TS_TimeStruct_t b = {0,0,0,0,30,10,100};
    TS_TimeStruct_t expected_result = {0,1,0,1,15,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_days_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,12,10,10,100};
    TS_TimeStruct_t b = {0,0,0,12,10,10,100};
    TS_TimeStruct_t expected_result = {0,1,1,0,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_days_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,0,12,10,10,100};
    TS_TimeStruct_t b = {0,0,0,18,10,10,100};
    TS_TimeStruct_t expected_result = {0,1,1,6,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,12,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,2,1,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,1,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,20,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,2,9,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_part3(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,4,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,20,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,5,10,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_part4(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,4,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,20,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,5,10,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_febuary_in_leap_year(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,2,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,20,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,3,11,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_months_febuary_in_non_leap_year(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {1,2,20,10,10,10,100};
    TS_TimeStruct_t b = {0,0,20,10,10,10,100};
    TS_TimeStruct_t expected_result = {0,3,12,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_years_part1(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,6,10,10,10,10,100};
    TS_TimeStruct_t b = {0,6,10,10,10,10,100};
    TS_TimeStruct_t expected_result = {1,1,20,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

void test_TimeStructCalc_add_roll_over_to_years_part2(void)
{
    //ARRANGE
    TS_TimeStruct_t a = {0,6,10,10,10,10,100};
    TS_TimeStruct_t b = {0,10,10,10,10,10,100};
    TS_TimeStruct_t expected_result = {1,4,20,20,20,20,200};

    //ACT
    TS_TimeStruct_t result = TimeStruct_add(a,b);

    //ASSERT
    TEST_ASSERT_EQUAL_MEMORY(&expected_result, &result, sizeof(TS_TimeStruct_t));

}

#endif // TEST