cmake_minimum_required(VERSION 2.8.9)
include(GNUInstallDirs)
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

set_target_properties(cpptimer PROPERTIES
  PUBLIC_HEADER CppTimer.h)

install(TARGETS cpptimer
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
