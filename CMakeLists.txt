cmake_minimum_required(VERSION 3.1)
if (UNIX)
    set(CMAKE_C_COMPILER "/usr/bin/gcc-10")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
endif (UNIX)
project(CLSelector)

if (UNIX)
    set (CMAKE_CXX_FLAGS "-std=gnu++20")
endif (UNIX)

if (APPLE)  
    set(CMAKE_CXX_STANDARD 17)
endif (APPLE)

# Build Server
execute_process (
    COMMAND bash -c "ln -s ${PROJECT_SOURCE_DIR}/MasterNode/configuration.h ${PROJECT_SOURCE_DIR}/SubNode/configuration.h"
)
add_subdirectory(MasterNode)
add_subdirectory(SubNode)
