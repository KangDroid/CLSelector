cmake_minimum_required(VERSION 3.1)
if (UNIX)
set(CMAKE_C_COMPILER "/usr/bin/gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")
endif (UNIX)
project(CLSelector_SubNode)

if (UNIX)
    set (CMAKE_CXX_FLAGS "-std=gnu++20")
endif (UNIX)

if (APPLE)  
    set(CMAKE_CXX_STANDARD 17)
endif (APPLE)

add_executable(CLSelector_SubNode main.cpp Server.cpp Client.cpp Logger.cpp)
