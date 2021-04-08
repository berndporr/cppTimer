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

add_executable (test_startstop_ms startstop_ms.cpp)
TARGET_LINK_LIBRARIES(test_startstop_ms cpptimer)
add_test(TestStartStop_ms test_startstop_ms)

add_executable (test_twotimers_ms twotimers_ms.cpp)
TARGET_LINK_LIBRARIES(test_twotimers_ms cpptimer)
add_test(TestTwotimers_ms test_twotimers_ms)
