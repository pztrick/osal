#ifndef INCLUDE_OS_FREERTOS_H
#define INCLUDE_OS_FREERTOS_H

// FreeRTOS headers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

// #include <os-shared-globaldefs.h>
#include "os-shared-common.h"
#include "os-shared-task.h"
#include "os-shared-queue.h"
#include "os-shared-printf.h"
#include "os-shared-timebase.h"
#include "os-shared-mutex.h"
#include "os-shared-countsem.h"
#include "os-shared-binsem.h"

#include "osapi.h"
#include "common_types.h"

int32 OS_FreeRTOS_TaskAPI_Impl_Init(void);
int32 OS_FreeRTOS_QueueAPI_Impl_Init(void);
int32 OS_FreeRTOS_BinSemAPI_Impl_Init(void);
int32 OS_FreeRTOS_CountSemAPI_Impl_Init(void);
int32 OS_FreeRTOS_MutexAPI_Impl_Init(void);
int32 OS_FreeRTOS_TimeBaseAPI_Impl_Init(void);
int32 OS_FreeRTOS_ModuleAPI_Impl_Init(void);
int32 OS_FreeRTOS_StreamAPI_Impl_Init(void);
int32 OS_FreeRTOS_DirAPI_Impl_Init(void);
int32 OS_FreeRTOS_FileSysAPI_Impl_Init(void);

int32 OS_FreeRTOS_TableMutex_Init(osal_objtype_t idtype);

#endif /* INCLUDE_OS_FREERTOS_H */
