cmake_minimum_required(VERSION 3.3)

set(SOURCE_FILES
        TestRunner.cpp
        MathTests/MathTests.cpp)

add_executable(testRunner ${SOURCE_FILES})

target_link_libraries(testRunner gtest gtest_main)
