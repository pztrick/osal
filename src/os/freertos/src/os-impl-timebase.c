#include <os-shared-globaldefs.h>
#include "os-impl-timebase.h"
#include "os-freertos.h"

// globals
OS_impl_timebase_internal_record_t OS_impl_timebase_table[OS_MAX_TIMEBASES];

int32 OS_FreeRTOS_TimeBaseAPI_Impl_Init(void)
{
    if(INCLUDE_vTaskDelay != 1){
        OS_DEBUG("ERROR: FreeRTOS requires FreeRTOS.h:INCLUDE_vTaskDelay to be configured to a value of 1 in order that portMAX_DELAY blocks indefinitely (as needed for some time-blocking behavior, etc).")
        return OS_ERROR;
    }

    OS_SharedGlobalVars.TicksPerSecond = (int32) configTICK_RATE_HZ;

    OS_SharedGlobalVars.MicroSecPerTick = 1000000 / configTICK_RATE_HZ;

    return OS_SUCCESS;
} 

int32 OS_TimeBaseCreate_Impl(const OS_object_token_t *token){
    // @FIXME
    return -1;
}

int32 OS_TimeBaseSet_Impl(const OS_object_token_t *token, uint32 start_time, uint32 interval_time){
    // @FIXME
    return -1;
}

int32 OS_TimeBaseDelete_Impl(const OS_object_token_t *token){
    // @FIXME
    return -1;
}

void OS_TimeBaseLock_Impl(const OS_object_token_t *token){
    // @FIXME
    return;
}

void OS_TimeBaseUnlock_Impl(const OS_object_token_t *token){
    // @FIXME
    return;
}

int32 OS_TimeBaseGetInfo_Impl(const OS_object_token_t *token, OS_timebase_prop_t *timer_prop){
    // @FIXME
    return -1;
}