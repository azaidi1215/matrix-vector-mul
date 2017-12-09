cmake_minimum_required(VERSION 3.9)
project(CLionProjects)

set(CMAKE_CXX_STANDARD 11)
SET( CMAKE_CXX_FLAGS  -pthread)

add_executable(CLionProjects main.cpp functions.h functions.cpp)