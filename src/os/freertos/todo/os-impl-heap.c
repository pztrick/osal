#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "common_types.h"
#include "osapi.h"
#include "osapi-os-core.h"
#include "os-shared-globaldefs.h"
#include "os-freertos.h"

HeapStats_t heapStats;

int32 OS_HeapGetInfo_Impl(OS_heap_prop_t *heap_prop){
    return OS_ERROR;  // @FIXME
}