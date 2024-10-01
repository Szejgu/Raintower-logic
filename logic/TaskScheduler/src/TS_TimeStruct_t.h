#ifndef TS_TimeStruct_T_H_
#define TS_TimeStruct_T_H_

#include <stdint.h>

typedef struct{

    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t milisecond;

}TS_TimeStruct_t;

#endif