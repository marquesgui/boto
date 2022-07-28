cmake_minimum_required(VERSION 3.22)
project(boto)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

add_executable(boto main.cpp)

target_include_directories(boto PRIVATE dependencies)

