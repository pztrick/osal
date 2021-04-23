#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "generic_freertos_bsp_internal.h"
#include "bsp-impl.h"

extern void PSP_Console_Write(char* buffer);

void OS_BSP_ConsoleOutput_Impl(const char *Str, size_t DataLen){
    PSP_Console_Write((char*) Str);
}

void OS_BSP_ConsoleSetMode_Impl(uint32 ModeBits){
    // no-op
}
