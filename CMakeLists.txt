cmake_minimum_required(VERSION 3.1.0)
include(GNUInstallDirs)
enable_testing()
project (CppTimer)
add_executable(demo demo.cpp)
set (CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wconversion -Wextra -pedantic)
TARGET_LINK_LIBRARIES(demo cpptimer)

add_library(cpptimer STATIC CppTimer.cpp)
TARGET_LINK_LIBRARIES(cpptimer rt)
set_target_properties(cpptimer PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_executable(demo_runnable demo_runnable.cpp)
TARGET_LINK_LIBRARIES(demo_runnable cpptimer)

add_subdirectory(test)

set_target_properties(cpptimer PROPERTIES
  PUBLIC_HEADER CppTimer.h)

install(TARGETS cpptimer
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
