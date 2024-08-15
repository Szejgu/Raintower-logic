# Minimum version check
cmake_minimum_required(VERSION 3.10)

# Set the toolchain symbol to point to a file - this allows for using arm toolchain
set(CMAKE_TOOLCHAIN_FILE Toolchain-arm-gcc.cmake)

# Allow assembler as we need it for startup file
enable_language(ASM)

# Set project name - used in various places
project(Raintower-logic)

# Set the build type according to the user input 
# Compiler flags are based on the build type 
if(NOT CMAKE_BUILD_TYPE)    
    message(FATAL_ERROR "CMAKE_BUILD_TYPE is required. Please set it using -DCMAKE_BUILD_TYPE:STRING=<value>. Valid values: UNITY / DEBUG / RELEASE.")
endif() 
message("Build type selected: ${CMAKE_BUILD_TYPE}")

# Variable definition is needed to pass -DUNITY_INCLUDE_CONFIG_H so that Unit uses unity_config.h when building Unity type builds
set(GLOBAL_DEFINES)

if(CMAKE_BUILD_TYPE STREQUAL "Unity")
    add_subdirectory(${CMAKE_SOURCE_DIR}/UNITY)
endif()

include(paths_and_defines.cmake)

include(Toolchain-arm-gcc.cmake)

# include a file containing the platform specific compiler flags
include(compiler_flags.cmake)

# Tell CMake to look for include directories listed in the helper symbol
include_directories(${INCLUDE_DIRS})

# Add definitions for needed by STM sources
add_definitions(${GLOBAL_DEFINES})

# Set the output directory for executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/platform/EXE)

# generate elf file using macros defined in Toolchain-arm-gcc.cmake
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})
