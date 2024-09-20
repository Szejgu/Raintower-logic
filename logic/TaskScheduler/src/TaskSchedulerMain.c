#include "TaskSchedulerMain.h"

TS_InitErrorCodes_t TS_Init(TS_InitStruct_t* input)
{
    return TS_InitErrorCodes_unknownError;
}

void TS_UpdateWakeupStatus(bool status)
{
    (void)status;   
}

void TS_Run(void)
{

}

TS_TimeStruct TS_PlanAbsolute(TS_TimeStruct date)
{

}

bool TS_DidTimeoutOccur(void)
{
    return true;
}