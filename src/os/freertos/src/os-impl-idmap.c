#include <os-shared-globaldefs.h>

#include "os-freertos.h"

// globals
SemaphoreHandle_t OS_task_table_sem;
SemaphoreHandle_t OS_queue_table_sem;
SemaphoreHandle_t OS_bin_sem_table_sem;
SemaphoreHandle_t OS_mutex_table_sem;
SemaphoreHandle_t OS_count_sem_table_sem;
SemaphoreHandle_t OS_stream_table_mut;
SemaphoreHandle_t OS_dir_table_mut;
SemaphoreHandle_t OS_timebase_table_mut;
SemaphoreHandle_t OS_timecb_table_mut;
SemaphoreHandle_t OS_module_table_mut;
SemaphoreHandle_t OS_filesys_table_mut;
SemaphoreHandle_t OS_console_mut;

static SemaphoreHandle_t *const MUTEX_TABLE[] = {
    [OS_OBJECT_TYPE_UNDEFINED]   = NULL,
    [OS_OBJECT_TYPE_OS_TASK]     = &OS_task_table_sem,
    [OS_OBJECT_TYPE_OS_QUEUE]    = &OS_queue_table_sem,
    [OS_OBJECT_TYPE_OS_COUNTSEM] = &OS_count_sem_table_sem,
    [OS_OBJECT_TYPE_OS_BINSEM]   = &OS_bin_sem_table_sem,
    [OS_OBJECT_TYPE_OS_MUTEX]    = &OS_mutex_table_sem,
    [OS_OBJECT_TYPE_OS_STREAM]   = &OS_stream_table_mut,
    [OS_OBJECT_TYPE_OS_DIR]      = &OS_dir_table_mut,
    [OS_OBJECT_TYPE_OS_TIMEBASE] = &OS_timebase_table_mut,
    [OS_OBJECT_TYPE_OS_TIMECB]   = &OS_timecb_table_mut,
    [OS_OBJECT_TYPE_OS_MODULE]   = &OS_module_table_mut,
    [OS_OBJECT_TYPE_OS_FILESYS]  = &OS_filesys_table_mut,
    [OS_OBJECT_TYPE_OS_CONSOLE]  = &OS_console_mut,
};

enum
{
    MUTEX_TABLE_SIZE = (sizeof(MUTEX_TABLE) / sizeof(MUTEX_TABLE[0]))
};

/*----------------------------------------------------------------
    Function: OS_Lock_Global_Impl
 ------------------------------------------------------------------*/
int32 OS_Lock_Global_Impl(osal_objtype_t idtype){
    SemaphoreHandle_t *mut;

    if(idtype < MUTEX_TABLE_SIZE){
        mut = MUTEX_TABLE[idtype];
    }else{
        mut = NULL;
    }

    if(mut == NULL){
        return OS_ERROR;
    }

    if(xSemaphoreTake(*mut, portMAX_DELAY) != pdTRUE){
        return OS_ERROR;
    }

    return OS_SUCCESS;
}

/*----------------------------------------------------------------
    Function: OS_Unlock_Global_Impl
 ------------------------------------------------------------------*/
int32 OS_Unlock_Global_Impl(osal_objtype_t idtype){
    SemaphoreHandle_t *mut;

    if(idtype < MUTEX_TABLE_SIZE){
        mut = MUTEX_TABLE[idtype];
    }else{
        mut = NULL;
    }

    if(mut == NULL){
        return OS_ERROR;
    }

    if(xSemaphoreGive(*mut) != pdTRUE){
        return OS_ERROR;
    }

    return OS_SUCCESS;
}


/*---------------------------------------------------------------------------------------
    Name: OS_FreeRTOS_TableMutex_Init
---------------------------------------------------------------------------------------*/
int32 OS_FreeRTOS_TableMutex_Init(osal_objtype_t idtype)
{
    int32 return_code = OS_SUCCESS;

    if(idtype < MUTEX_TABLE_SIZE && MUTEX_TABLE[idtype] != NULL){
        // @FYI Consider using xSemaphoreCreateMutexStatic to define specific RAM address
        // @FYI Consider using Binary Semaphore in place of Mutex if interrupts will be able to access mutex
        //      See: https://www.freertos.org/Embedded-RTOS-Binary-Semaphores.html

        // Create mutex
        *MUTEX_TABLE[idtype] = xSemaphoreCreateMutex();
        if(*MUTEX_TABLE[idtype] == NULL){
            OS_DEBUG("Error: xSemaphoreCreateMutex failed: %d\n", idtype);
            return OS_ERROR;
        }
        // Take the mutex
        if(xSemaphoreTake(*MUTEX_TABLE[idtype], (TickType_t) 0) == pdTRUE){
            // Release the mutex
            if(xSemaphoreGive(*MUTEX_TABLE[idtype]) != pdTRUE){
                return OS_ERROR;
            }
        }else {
            return OS_ERROR;
        }
    }

    return return_code;
}
