#include <os-shared-globaldefs.h>
#include "os-impl-task.h"

// globals definitions
OS_impl_task_internal_record_t OS_impl_task_table[OS_MAX_TASKS];


/*----------------------------------------------------------------
 * Function: OS_FreeRTOS_TaskAPI_Impl_Init
 *-----------------------------------------------------------------*/
int32 OS_FreeRTOS_TaskAPI_Impl_Init(void)
{
    memset(OS_impl_task_table, 0, sizeof(OS_impl_task_table));
    return (OS_SUCCESS);
} /* end OS_FreeRTOS_TaskAPI_Impl_Init */


static void OS_FreeRTOS_TaskEntryPoint(void *pvParameters)
{
    int obj_id = *(int *) pvParameters;
    OS_TaskEntryPoint(OS_ObjectIdFromInteger(obj_id));
}

/*----------------------------------------------------------------
   Function: OS_TaskMatch_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskMatch_Impl(const OS_object_token_t *token){
    // OS_task_internal_record_t *task;
    OS_impl_task_internal_record_t *impl;

    // task = OS_OBJECT_TABLE_GET(OS_task_table, *token);
    impl = OS_OBJECT_TABLE_GET(OS_impl_task_table, *token);

    TaskHandle_t current_task;
    current_task = xTaskGetCurrentTaskHandle();

    if(impl->xTask == current_task){
      return OS_SUCCESS;
    }

    return OS_ERROR;
}

/*----------------------------------------------------------------
   Function: OS_TaskCreate_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskCreate_Impl(const OS_object_token_t *token, uint32 flags){
    OS_impl_task_internal_record_t *impl;
    OS_task_internal_record_t *task;
    BaseType_t xReturnCode;

    impl = OS_OBJECT_TABLE_GET(OS_impl_task_table, *token);
    task = OS_OBJECT_TABLE_GET(OS_task_table, *token);

    if(task->priority > configMAX_PRIORITIES){
      OS_printf("Task priority cannot exceed FreeRTOSConfig.h:configMAX_PRIORITIES=%d\n", configMAX_PRIORITIES);
      return OS_ERROR;
    }

    impl->obj_id = OS_ObjectIdToInteger(OS_ObjectIdFromToken(token));
    sprintf(impl->obj_id_str, "%lu", impl->obj_id);

    // create task
    //  xTaskCreate allocates from FreeRTOS heap
    //  xTaskCreateStatic is allocated ahead of calling OS_TaskCreate (with task->stack_pointer)
    if(task->stack_pointer == NULL){
        xReturnCode = xTaskCreate(
            OS_FreeRTOS_TaskEntryPoint,
            impl->obj_id_str,
            task->stack_size,
            &impl->obj_id,  // pvParameters
            task->priority,
            (TaskHandle_t *) &impl->xTask  // pxCreatedTask handle
        );
    }else{
        OS_printf("Providing an already allocated stack to OS_TaskCreate is not implemented.\n");
        return OS_ERROR;
    }


    if(xReturnCode != pdTRUE){
        OS_printf("xTaskCreate %s failed.\n", task->task_name);
        return OS_ERROR;
    }

    return OS_SUCCESS;
}

/*----------------------------------------------------------------
   Function: OS_TaskDelete_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskDelete_Impl(const OS_object_token_t *token){
    OS_impl_task_internal_record_t *impl;

    impl = OS_OBJECT_TABLE_GET(OS_impl_task_table, *token);

    vTaskDelete(impl->xTask);

    // @FIXME null the impl table

    return OS_SUCCESS;
}

/*----------------------------------------------------------------
   Function: OS_TaskExit_Impl
 ------------------------------------------------------------------*/
void OS_TaskExit_Impl(void){
    vTaskDelete(NULL);

    // @FIXME null the impl table
}

/*----------------------------------------------------------------
   Function: OS_TaskDelay_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskDelay_Impl(uint32 millisecond){
    vTaskDelay(millisecond / portTICK_PERIOD_MS);
    return OS_SUCCESS;
}

/*----------------------------------------------------------------
   Function: OS_TaskSetPriority_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskSetPriority_Impl(const OS_object_token_t *token, osal_priority_t new_priority){
    return OS_ERROR; // @FIXME
}

/*----------------------------------------------------------------
   Function: OS_TaskGetId_Impl
 ------------------------------------------------------------------*/
osal_id_t OS_TaskGetId_Impl(void){
    osal_id_t global_task_id;
    char *task_name;
    task_name = pcTaskGetName(NULL);
    if(sscanf(task_name, "%lu", &global_task_id) == 1){
        return global_task_id;
    }
    return 0;
}

/*----------------------------------------------------------------
   Function: OS_TaskGetInfo_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskGetInfo_Impl(const OS_object_token_t *token, OS_task_prop_t *task_prop){
  return OS_ERROR; // @FIXME
}

/*----------------------------------------------------------------
   Function: OS_TaskRegister_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskRegister_Impl(osal_id_t global_task_id){
    // we already save impl->obj_id in OS_TaskCreate_Impl()
    // @FIXME we could construct a hash table here to
    // look up global_task_id faster in OS_TaskGetId_Impl()
    return OS_SUCCESS;
}

/*----------------------------------------------------------------
   Function: OS_TaskIdMatchSystemData_Impl
 ------------------------------------------------------------------*/
bool OS_TaskIdMatchSystemData_Impl(void *ref, const OS_object_token_t *token, const OS_common_record_t *obj){
    return false; // @FIXME
}

/*----------------------------------------------------------------
   Function: OS_TaskValidateSystemData_Impl
 ------------------------------------------------------------------*/
int32 OS_TaskValidateSystemData_Impl(const void *sysdata, size_t sysdata_size){
    return OS_ERROR; // @FIXME
}

