#include "TimeStructCalc.h"
#include <stdbool.h>

#define MONTH_SHORT_MASK 0x00001C1A12041018
#define MONTH_LONG_MASK 0x00001C1A02041018
#define MONTH_FEB_LEAP 0x00001C1A22041018
#define MONHT_FEB_COMMON 0x00001C1A32041018

typedef enum{

    Month_short = 0x01,
    Month_long = 0x02,
    Month_febuary_leap = 0x03,
    Month_febuary_common = 0x04,

    Month_incorrect_mask = 0xFF

}Month_mask_t;


static uint64_t add_time_struct(uint64_t* a, uint64_t* b, Month_mask_t mask_select);

static bool isLeapYear(uint8_t yearsSince2000);

TS_TimeStruct_t TimeStruct_add(TS_TimeStruct_t base, TS_TimeStruct_t time)
{
    TS_TimeStruct_t ret = {0};
    Month_mask_t mask = Month_incorrect_mask;

    switch(base.data.month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            mask = Month_long;
        break;

        case 4:
        case 6:
        case 9:
        case 11:
            mask = Month_short;
        break;

        case 2:
            if(isLeapYear(base.data.year))
            {
                mask = Month_febuary_leap;
            }
            else
            {
                mask = Month_febuary_common;
            }
        break;

        default:
            mask = Month_incorrect_mask;
        break;
    }
 
    ret.raw = add_time_struct(&base.raw, &time.raw, mask);

    if(ret.data.hour_overflow > 0)
    {
        ret.data.day += 1;
    }

    if(ret.data.day_overflow > 0)
    {
        ret.data.month += 1;
        ret.data.day += 1;
    }

    if(ret.data.month_overflow > 0)
    {
        ret.data.month += 1;
        ret.data.year += 1;
    }

    if(ret.data.day == 0)
    {
        ret.data.day = 1;
    }

    if(ret.data.month == 0)
    {
        ret.data.month = 1;
    }

    ret.data.day_overflow = 0;
    ret.data.hour_overflow = 0;
    ret.data.month_overflow = 0;

    return ret;
}

TS_TimeStruct_ComparisonResult_t TimeStruct_compare(TS_TimeStruct_t target, TS_TimeStruct_t secondary)
{
    TS_TimeStruct_ComparisonResult_t ret = TimeStruct_equal;

    return ret;
}

static uint64_t add_time_struct(uint64_t* a, uint64_t* b, Month_mask_t mask_select)
{
    uint64_t limits = 0;
    uint64_t t15 = 0;

    switch(mask_select)
    {
        case Month_short:
            limits = MONTH_SHORT_MASK;
        break;
        
        case Month_febuary_common:
            limits = MONHT_FEB_COMMON;
        break;

        case Month_febuary_leap:
            limits = MONTH_FEB_LEAP;
        break;

        case Month_long:
        default:
            limits = MONTH_LONG_MASK;
        break;
    }

    uint64_t t1 = *a + limits;
    uint64_t t2 = t1 + *b;
    uint64_t t3 = ~(t1 ^ *b ^ t2);
    
    uint64_t t4 = t3 & 0x0000000000000400;
    uint64_t t5 = t3 & 0x0000000000010000;
    uint64_t t6 = t3 & 0x0000000000400000;
    uint64_t t7 = t3 & 0x0000000008000000;
    uint64_t t8 = t3 & 0x0000000400000000;
    uint64_t t9 = t3 & 0x0000008000000000;
    uint64_t t10 = t3 & 0x0000800000000000;
    
    uint64_t t11 = (t4 >> 6) | (t4 >> 7);
    uint64_t t12 = (t5 >> 4);
    uint64_t t13 = (t6 >> 4);
    uint64_t t14 = (t7 >> 2);
        switch(mask_select)
    {
        case Month_short:
            t15 = (t8 >> 1) | (t8 >> 6);
        break;
        
        case Month_febuary_common:
            t15 = (t8 >> 1) | (t8 >> 5) | (t8 >> 6);
        break;

        case Month_febuary_leap:
            t15 = (t8 >> 1) | (t8 >> 5);
        break;

        case Month_long:
        default:
            t15 = (t8 >> 1);
        break;
    }
    uint64_t t16 = (t9 >> 3) | (t9 >> 4);
    uint64_t t17 = (t10 >> 3) | (t10 >> 4) | (t10 >> 5);

    return t2 - (t11 | t12 | t13 | t14 | t15 | t16 | t17);

}

static bool isLeapYear(uint8_t yearsSince2000)
{
    return (0 == (yearsSince2000 % 4)) ? true : false;
}