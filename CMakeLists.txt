cmake_minimum_required(VERSION 3.3)
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(billiards)

set(SOURCE_FILES
        src/math/Vec.cpp
        src/math/Vec.h
        src/objects/Mesh.cpp
        src/objects/Mesh.h
        src/objects/Model.cpp
        src/objects/Model.h
        src/shader/Shader.cpp
        src/shader/Shader.h
        src/util/Util.cpp
        src/util/Util.h)
include_directories(src/math src/shader src/util src/objects)
add_executable(billiards src/main.cpp ${SOURCE_FILES})
target_link_libraries(billiards GL GLEW glfw m)

set(TEST_SOURCE_FILES
        tests/mathTests/VecTests.cpp)
add_executable(runTests tests/TestRunner.cpp ${TEST_SOURCE_FILES} ${SOURCE_FILES})
target_link_libraries(runTests gtest gtest_main GL GLEW glfw m)