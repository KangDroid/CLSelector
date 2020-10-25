cmake_minimum_required(VERSION 3.1)
project(CLSelector)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLSelector main.cpp Device.cpp Client.cpp)

# Build Server
add_subdirectory(server)