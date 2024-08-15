# -------------------------- PREPARE HELPER SYMBOLS -------------------------
# Set the helper symbol for include directories
set(INCLUDE_DIRS
    platform/CMSIS/Device/ST/STM32WLxx/Include
    platform/CMSIS/Include
    platform/Inc
)

set(C_SRCS

#------------PLATFORM RELATED SOURCE FILES ----------------------------------------------------------
	platform/Src/system_stm32wlxx.c
	platform/Src/System.c


#------------EXTERNAL LIBS RELATED SOURCE FILES ----------------------------------------------------

#------------THE BIG BOI ---------------------------------------------------------------------------
    platform/Src/main.c
)
if(CMAKE_BUILD_TYPE STREQUAL "Unity")
    set(C_SRCS ${C_SRCS} src/UnityHooks.c)
endif()


set(ASM_SRCS
    platform/Src/startup_stm32wl55xx_cm4.s
)

# Linker Script
set(LD_SCRIPT platform/linker/STM32WL55XX_FLASH_CM4.ld)

set(STM32_DEFINES
    -DUSE_FULL_LL_DRIVER 
	-DCORE_CM4 
	-DSTM32WL55xx
	-DLSE_VALUE=32768 
)
set(GLOBAL_DEFINES ${GLOBAL_DEFINES} ${STM32_DEFINES})


