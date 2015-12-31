cmake_minimum_required(VERSION 3.3)
project(billiards)

set(SOURCE_FILES
        main.cpp)

add_executable(billiards ${SOURCE_FILES})

add_subdirectory(tests)

add_custom_target(tests COMMAND tests/testRunner --gtest_color=yes)