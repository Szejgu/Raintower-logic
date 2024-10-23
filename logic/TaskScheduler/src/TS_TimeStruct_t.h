#ifndef TS_TimeStruct_T_H_
#define TS_TimeStruct_T_H_

#include <stdint.h>

typedef struct __attribute__((packed)){

    #if(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

        uint64_t milisecond : 10;
        uint64_t second : 6;
        uint64_t minute : 6;
        uint64_t hour : 5;
        uint64_t hour_overflow : 1;
        uint64_t day : 6;
        uint64_t day_overflow : 1;
        uint64_t month : 4;
        uint64_t month_overflow : 1;
        uint64_t year : 7;
        uint64_t unused : 17;

    #elif(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

        uint64_t unused : 17;
        uint64_t year : 7;
        uint64_t month_overflow : 1;
        uint64_t month : 4;
        uint64_t day_overflow : 1;
        uint64_t day : 6;
        uint64_t hour_overflow : 1;
        uint64_t hour : 5;
        uint64_t minute : 6;
        uint64_t second : 6;
        uint64_t milisecond : 10;

    #else
        #error "Unsupported architecture"
    #endif

}TS_TimeStruct_data_t;

typedef union{

    TS_TimeStruct_data_t data;
    uint64_t raw;
    
}TS_TimeStruct_t;

_Static_assert(sizeof(TS_TimeStruct_data_t) == sizeof(uint64_t), "Wrong substructure size" );
_Static_assert(sizeof(TS_TimeStruct_t) == sizeof(uint64_t), "Wrong time struct size" );

#endif