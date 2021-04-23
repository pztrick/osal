#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "common_types.h"
#include "osapi.h"
#include "osapi-os-core.h"
#include "osapi-os-filesys.h"
#include "os-shared-globaldefs.h"
#include "os-freertos.h"

// @TODO @FIXME
int32 OS_FreeRTOS_FileSysAPI_Impl_Init(void){
    return OS_SUCCESS;
}
int32 OS_FreeRTOS_DirAPI_Impl_Init(void){
    return OS_SUCCESS;
}
int32 OS_FileAPI_Init(void){
    return OS_SUCCESS;
}
int32 OS_FileSysAPI_Init(void){
    return OS_SUCCESS;
}
int32 OS_DirAPI_Init(void){
    return OS_SUCCESS;
}
int32 OS_DirectoryClose(osal_id_t dir_id){
    return -1;
}
int32 OS_OpenCreate(osal_id_t *filedes, const char *path, int32 flags, int32 access){
    return -1;
}
int32 OS_close(osal_id_t filedes){
    return -1;
}
int32 OS_fsBlocksFree(const char *name){
    return -1;
}
int32 OS_initfs(char *address, const char *devname, const char *volname, size_t blocksize, osal_blockcount_t numblocks){
    return -1;
}
int32 OS_lseek(osal_id_t filedes, int32 offset, uint32 whence){
    return -1;
}
int32 OS_mkfs(char *address, const char *devname, const char *volname, size_t blocksize, osal_blockcount_t numblocks){
    return -1;
}
int32 OS_mount(const char *devname, const char *mountpoint){
    return -1;
}
int32 OS_read(osal_id_t filedes, void *buffer, size_t nbytes){
    return -1;
}
int32 OS_remove(const char *path){
    return -1;
}
int32 OS_rmfs(const char *devname){
    return -1;
}
int32 OS_stat(const char *path, os_fstat_t *filestats){
    return -1;
}
int32 OS_unmount(const char *mountpoint){
    return -1;
}
int32 OS_write(osal_id_t filedes, const void *buffer, size_t nbytes){
    return -1;
}