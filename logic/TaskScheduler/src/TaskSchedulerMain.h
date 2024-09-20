#ifndef TASKSCHEDULERMAIN_H
#define TASKSCHEDULERMAIN_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum{

    TS_Priority_low = 0x00,
    TS_Priority_normal = 0x01,
    TS_Priority_high = 0x02

}TaskPriority_t;

typedef struct{

    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t milisecond;

}TS_TimeStruct;

#define TASK_LIMIT_STRUCT { \
    .year = 0, \
    .month = 0, \
    .day = 0, \
    .hour = 0, \
    .minute = 0, \
    .second = 5, \
    .milisecond = 0 \
    } 

typedef struct{

    void (*TaskFunPtr)(void);
    TS_TimeStruct (*PlanNextInst)(void);
    TaskPriority_t Priority;
    TS_TimeStruct MaximumExecTime;
    TS_TimeStruct* TimeToNextInst;

}TaskDescriptor_t;



typedef struct{

    TaskDescriptor_t* TaskListTab;
    size_t TaskListTab_size;
    
    void (*updateCurrentTimeFromHW)(TS_TimeStruct* input);
    bool (*setCurrentTimeInHW)(const TS_TimeStruct* input);

    bool (*setNextWakeup)(const TS_TimeStruct* input);

    bool (*setOrRestartTaskBreaker)(const TS_TimeStruct* input);
    bool (*resetTaskBreaker)(void);

}TS_InitStruct_t;


typedef enum{

    TS_InitErrorCodes_noError = 0x00,
    TS_InitErrorCodes_TaskList_NULL,
    TS_InitErrorCodes_TaskList_Integrity_error,
    TS_InitErrorCodes_updateCurrentTimeFromHW_NULL,
    TS_InitErrorCodes_setCurrentTimeInHW_NULL,
    TS_InitErrorCodes_setNextWakeup_NULL,
    TS_InitErrorCodes_setOrRestartTaskBreaker_NULL,
    TS_InitErrorCodes_resetTaskBreaker_NULL,

    TS_InitErrorCodes_unknownError = 0xFF

}TS_InitErrorCodes_t;

TS_InitErrorCodes_t TS_Init(TS_InitStruct_t* input);

/**
 * @brief Updates the internal state, so that the module has the information that the wakeup that happened was from scheduled alarm
 */
void TS_UpdateWakeupStatus(bool status);

/**
 * @brief The function that recalculates the task array and executes the task
 */
void TS_Run(void);

/**
 * @brief Helper function which translates the given time struct in such a way that the resulting struct is an absolute date
 * @remark Any other time struct given as a result of Plan Next is a relative representation of next occurence
 * @remark with this function it's possible to plan for specific minute/day/hour rather than planning after a given ammount of time
 */
TS_TimeStruct TS_PlanAbsolute(TS_TimeStruct date);

/**
 * @brief This function is for use for other modules to signify the task execution time has been exceeded
 */
bool TS_DidTimeoutOccur(void);


#endif // TASKSCHEDULERMAIN_H
