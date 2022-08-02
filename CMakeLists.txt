cmake_minimum_required(VERSION 3.22)
project(boto)
set(CMAKE_CXX_STANDARD 17)

###################################
###        Modules Path         ###
###################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

###################################
###         GoogleTest          ###
###################################
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
enable_testing()

###################################
###          Binnary            ###
###################################
file(GLOB IMGUI_SRC vendor/imgui/*.cpp)

add_executable(boto
  src/main.cpp
  src/Core/Application.cpp
  src/Core/Event.cpp
  src/ImGui/ImGuiLayer.cpp
  src/ImGui/widgets/ContentBrowserPanel.cpp
  src/ImGui/widgets/MainMenuBar.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp
  vendor/imgui/backends/imgui_impl_glfw.cpp
  ${IMGUI_SRC})

#file(GLOB_RECURSE BOTO_TEST_SOURCES test/*.cpp)
#file(GLOB_RECURSE BOTO_SOURCES src/*.cpp)
#add_executable(boto_test ${BOTO_TEST_SOURCES})

###################################
###        Directories          ###
###################################
target_include_directories(boto PRIVATE vendor)

#include(GoogleTest)
#gtest_discover_tests(boto_test)
###################################
###      Linking libraries      ###
###################################
find_package(glfw3 REQUIRED)
if (TARGET glfw::glfw)
  target_link_libraries(boto glfw::glfw)
endif ()

find_package(GLEW REQUIRED)
if (TARGET GLEW::GLEW)
  target_link_libraries(boto GLEW::GLEW)
endif ()

#if (TARGET GTest::gtest_main)
#  target_link_libraries(boto_test GTest::gtest_main)
#endif()