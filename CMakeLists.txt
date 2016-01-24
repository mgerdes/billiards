cmake_minimum_required(VERSION 3.3)
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(billiards)

set(SOURCE_FILES
        src/camera/Camera.cpp
        src/light/Light.cpp
        src/material/Material.cpp
        src/math/Vector.cpp
        src/math/Matrix.cpp
        src/objects/BoundingObject.cpp
        src/objects/Mesh.cpp
        src/objects/Model.cpp
        src/resourceManager/ResourceManager.cpp
        src/shader/Shader.cpp
        src/simulation/BilliardsSimulation.cpp
        src/texture/Texture.cpp
        src/util/Util.cpp
        src/window/Window.cpp)
include_directories(src/camera
        src/light
        src/material
        src/math
        src/objects
        src/resourceManager
        src/shader
        src/simulation
        src/texture
        src/util
        src/window)
add_executable(billiards src/main.cpp ${SOURCE_FILES})
target_link_libraries(billiards GL GLEW glfw m assimp)

set(TEST_SOURCE_FILES
        tests/mathTests/VectorTests.cpp
        tests/mathTests/MatrixTests.cpp)
#add_executable(runTests tests/TestRunner.cpp ${TEST_SOURCE_FILES} ${SOURCE_FILES})
#target_link_libraries(runTests gtest gtest_main GL GLEW glfw m assimp)