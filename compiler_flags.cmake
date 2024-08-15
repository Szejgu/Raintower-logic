# Compiler flags used for C and ASM files
set(CORE_FLAGS "-mcpu=cortex-m4+nofp -march=armv7e-m -Wl,--no-warn-rwx-segment -mthumb -fdata-sections -ffunction-sections")

# Hardware float support
set(CORE_FLAGS "${CORE_FLAGS} -mfloat-abi=softfp -mfpu=auto")

# Compiler flags specific for C++ files
set(CXX_FLAGS "-std=gnu17 -fno-rtti -fno-exceptions -fverbose-asm -MMD")

# Compiler flags specific for C files
set(C_FLAGS "-std=gnu11 -fverbose-asm -MMD")

set(ASM_FLAGS "-x assembler-with-cpp")

# Warning flags for C++
set(CXX_WARNINGS "-Wall -Wextra")

# Warning flags for C
set(C_WARNINGS "-Wall -Wextra -Wstrict-prototypes")

# Linker flags
set(LD_FLAGS "-Wl,-Map=${CMAKE_SOURCE_DIR}/platform/EXE/${CMAKE_PROJECT_NAME}.map,--cref -T${LD_SCRIPT} -Wl,--gc-sections -static --specs=nano.specs -Wl,--print-memory-usage")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

	set(CORE_FLAGS "${CORE_FLAGS} -g -fdebug-prefix-map=${CMAKE_SOURCE_DIR}=.")
	set(CXX_FLAGS "${CXX_FLAGS} -O0")
	set(C_FLAGS "${C_FLAGS} -O0")
	set(LD_FLAGS "${LD_FLAGS}")

	
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

	set(CXX_FLAGS "${CXX_FLAGS} -O3")
	set(C_FLAGS "${C_FLAGS} -O3")

	
elseif(CMAKE_BUILD_TYPE STREQUAL "Unity")
	set(CORE_FLAGS "${CORE_FLAGS} -g -fdebug-prefix-map=${CMAKE_SOURCE_DIR}=.")
	set(CXX_FLAGS "${CXX_FLAGS} -O0")
	set(C_FLAGS "${C_FLAGS} -O0")
	set(LD_FLAGS "${LD_FLAGS}")
	set(GLOBAL_DEFINES "${GLOBAL_DEFINES} -DUNITY -DUNITY_INCLUDE_CONFIG_H")


endif()


set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")
set(CMAKE_ASM_FLAGS "${ASM_FLAGS} ${CORE_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CORE_FLAGS} ${LD_FLAGS}")
