#include <stdlib.h>
#include <string.h>

#include "generic_freertos_bsp_internal.h"

void OS_BSP_Shutdown_Impl(void){
    abort();  // @FIXME not implemented
}

#define PSP_CFE_TASK_STACKSIZE 1024
#define PSP_CFE_TASK_PRIORITY 4

TaskHandle_t cfe_psp_task_handle;

void PSP_CFE_Task(void *pvParameters){
    // This task initializes PSP and CFE after Task Scheduler started
    OS_Application_Startup();
    OS_Application_Run();
}

int main(void){
    memset(&OS_BSP_Global, 0, sizeof(OS_BSP_Global));

    xTaskCreate(
        &PSP_CFE_Task,
        "PSP_CFE_Task",
        PSP_CFE_TASK_STACKSIZE,
        NULL,  // pvParameters
        PSP_CFE_TASK_PRIORITY,
        &cfe_psp_task_handle  // pxCreatedTask handle
    );

    vTaskStartScheduler();

    return OS_BSP_Global.AppStatus;
}
