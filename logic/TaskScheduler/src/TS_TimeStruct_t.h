#ifndef TS_TimeStruct_T_H_
#define TS_TimeStruct_T_H_

#include <stdint.h>

typedef struct __attribute__((packed)){

    uint64_t milisecond : 10;
    uint64_t second : 6;
    uint64_t minute : 6;
    uint64_t hour : 5;
    uint64_t day : 6;
    uint64_t month : 4;
    uint64_t year : 7;
    uint64_t unused : 20;

}TS_TimeStruct_data_t;

typedef union{

    TS_TimeStruct_data_t data;
    uint64_t raw;
    
}TS_TimeStruct_t;



#endif