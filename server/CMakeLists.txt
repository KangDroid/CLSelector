cmake_minimum_required(VERSION 3.1)
project(CLSelector_Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLSelector_Server main.cpp Server.cpp)