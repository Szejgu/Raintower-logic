#include "TimeStructCalc.h"

static uint64_t add_time_struct(uint64_t* a, uint64_t* b);

TS_TimeStruct_t TimeStruct_add(TS_TimeStruct_t base, TS_TimeStruct_t time)
{
    TS_TimeStruct_t ret = {0};
    ret.raw = add_time_struct(&base.raw, &time.raw);
    return ret;
}

TS_TimeStruct_ComparisonResult_t TimeStruct_compare(TS_TimeStruct_t target, TS_TimeStruct_t secondary)
{
    TS_TimeStruct_ComparisonResult_t ret = TimeStruct_equal;

    return ret;
}

static uint64_t add_time_struct(uint64_t* a, uint64_t* b)
{
    uint64_t t1 = *a + 0x0000038702041018;
    uint64_t t2 = t1 + *b;
    uint64_t t3 = ~(t1 ^ *b ^ t2);
    
    uint64_t t4 = t3 & 0x0000000000000400;
    uint64_t t5 = t3 & 0x0000000000010000;
    uint64_t t6 = t3 & 0x0000000000400000;
    uint64_t t7 = t3 & 0x0000000008000000;
    uint64_t t8 = t3 & 0x0000000200000000;
    uint64_t t9 = t3 & 0x0000002000000000;
    uint64_t t10 = t3 & 0x0000100000000000;
    
    uint64_t t11 = (t4 >> 6) | (t4 >> 7);
    uint64_t t12 = (t5 >> 4);
    uint64_t t13 = (t6 >> 4);
    uint64_t t14 = (t7 >> 2);
    uint64_t t15 = (t8 >> 1);
    uint64_t t16 = (t9 >> 3) | (t9 >> 4);
    uint64_t t17 = (t10 >> 3) | (t10 >> 4) | (t10 >> 5);

    return t2 - (t11 | t12 | t13 | t14 | t15 | t16 | t17);

}
