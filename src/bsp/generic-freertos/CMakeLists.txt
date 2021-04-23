include_directories(${OSAL_FREERTOS_INC_DIR})
include_directories(${OSAL_FREERTOS_SRC_DIR}/portable/GCC/ARM_CM3)

add_library(osal_generic-freertos_impl OBJECT
    src/bsp_start.c
    src/bsp_console.c
)

set(OSAL_EXPECTED_OSTYPE "freertos" PARENT_SCOPE)
