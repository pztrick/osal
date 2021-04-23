#ifndef INCLUDE_OS_IMPL_TIMEBASE_H
#define INCLUDE_OS_IMPL_TIMEBASE_H

#include <osconfig.h>
#include "os-freertos.h"
#include "os-shared-idmap.h"
#include "os-shared-queue.h"

typedef struct
{
    int32 empty;
} OS_impl_timebase_internal_record_t;

extern OS_impl_timebase_internal_record_t OS_impl_timebase_table[OS_MAX_TIMEBASES];

#endif /* INCLUDE_OS_IMPL_TIMEBASE_H */
