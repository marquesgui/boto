cmake_minimum_required(VERSION 3.22)
project(boto)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

add_executable(boto main.cpp)

target_include_directories(boto PRIVATE dependencies)

find_package(glfw3 REQUIRED)
if (TARGET glfw::glfw)
  target_link_libraries(boto glfw::glfw)
endif ()

find_package(GLEW REQUIRED)
if (TARGET GLEW::GLEW)
  target_link_libraries(boto GLEW::GLEW)
endif ()