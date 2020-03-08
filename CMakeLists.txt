cmake_minimum_required(VERSION 2.8.9)
enable_testing()
project (demo)
add_executable(demo demo.cpp)
set (CMAKE_CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(demo cpptimer)

add_library(cpptimer STATIC CppTimer.cpp)
TARGET_LINK_LIBRARIES(cpptimer rt)

add_executable(demo_runnable demo_runnable.cpp)
TARGET_LINK_LIBRARIES(demo_runnable cpptimer)

add_subdirectory(test)
