#ifndef TIMESTRUCTCALC_H_
#define TIMESTRUCTCALC_H_

#include "TS_TimeStruct_t.h"

typedef enum{

    TimeStruct_lesser,
    TimeStruct_equal,
    TimeStruct_greater
    
}TS_TimeStruct_ComparisonResult_t;

TS_TimeStruct_t TimeStruct_add(TS_TimeStruct_t base, TS_TimeStruct_t time);

TS_TimeStruct_ComparisonResult_t TimeStruct_compare(TS_TimeStruct_t target, TS_TimeStruct_t secondary);

#endif