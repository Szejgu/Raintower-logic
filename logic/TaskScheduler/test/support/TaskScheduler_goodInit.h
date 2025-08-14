#ifndef TASKSCHEDULER_GOODINIT_H_
#define TASKSCHEDULER_GOODINIT_H_

#include "TaskSchedulerMain.h"

#define TASK_LIST_LENGTH 3

#define DUMMY_TASK_MAX_EXEC_TIME { \
    .data = { \
        .year = 0, \
        .month = 0, \
        .day = 0, \
        .hour = 0, \
        .minute = 0, \
        .second = 1, \
        .milisecond = 0 \
        }\
}

#define DUMMY_TASK_MAX_EXEC_TIME2 { \
    .data = {\
        .year = 0, \
        .month = 0, \
        .day = 0, \
        .hour = 0, \
        .minute = 0, \
        .second = 0, \
        .milisecond = 900 \
    }\
}

#define TASK_MAX_EXEC_TIME_ALL_ZERO {\
    .data = { \
        .year = 0, \
        .month = 0, \
        .day = 0, \
        .hour = 0, \
        .minute = 0, \
        .second = 0, \
        .milisecond = 0 \
        }\
}

extern TS_TimeStruct_t HWTimestampRet;
extern uint32_t HWTimestampGetCallCounter;
extern TS_TimeStruct_t alarmSetValue;

TS_InitStruct_t goodInit(void);


void dummy_getHWTimestamp(TS_TimeStruct_t* input);
bool dummy_setNextAlarm(const TS_TimeStruct_t* input);
bool dummy_setNextTaskBreaker(const TS_TimeStruct_t* input);
bool dummy_resetTaskbreaker(void);
TS_TimeStruct_t dummy_planNext(void);
void dummy_fun(void);
bool b_dummy_const_TS_TimeStruct_t(const TS_TimeStruct_t* input);
void v_dummy_TS_TimeStruct_t(TS_TimeStruct_t* input);
bool b_dummy_v(void);

#endif