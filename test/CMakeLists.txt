cmake_minimum_required(VERSION 2.8)
enable_testing()
include_directories(
  ..
  )

add_executable (test_startstop startstop.cpp)
TARGET_LINK_LIBRARIES(test_startstop cpptimer)
add_test(TestStartStop test_startstop)

add_executable (test_twotimers twotimers.cpp)
TARGET_LINK_LIBRARIES(test_twotimers cpptimer)
add_test(TestTwotimers test_twotimers)
