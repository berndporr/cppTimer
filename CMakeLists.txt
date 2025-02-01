cmake_minimum_required(VERSION 3.6)

project (CppTimer
  DESCRIPTION "Wrapper for Linux timers"
  LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wconversion -Wextra -pedantic)
include(GNUInstallDirs)
enable_testing()

add_library(cpptimer INTERFACE)

add_executable(demo demo.cpp)
TARGET_LINK_LIBRARIES(demo cpptimer)

add_executable(demo_runnable demo_runnable.cpp)
TARGET_LINK_LIBRARIES(demo_runnable cpptimer)

add_executable(demo_stdfunccallback demo_stdfunccallback.cpp)
TARGET_LINK_LIBRARIES(demo_stdfunccallback cpptimer)


add_subdirectory(test)

set_target_properties(cpptimer PROPERTIES
  PUBLIC_HEADER CppTimer.h)

install(TARGETS cpptimer
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
