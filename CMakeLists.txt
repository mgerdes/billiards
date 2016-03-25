cmake_minimum_required(VERSION 3.3)
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(billiards)

set(SOURCE_FILES
        src/camera/Camera.cpp
        src/light/Light.cpp
        src/material/Material.cpp
        src/math/Vector.cpp
        src/math/Vector3.cpp
        src/math/Matrix.cpp
        src/math/Quaternion.cpp
        src/objects/Mesh.cpp
        src/objects/Geometry.cpp
        src/objects/Object3D.cpp
        src/objects/Scene.cpp
        src/shader/Shader.cpp
        src/renderer/Renderer.cpp
        src/texture/Texture.cpp
        src/util/Util.cpp
        src/util/ResourceManager.cpp
        src/window/Window.cpp)
include_directories(src/camera
        src/light
        src/material
        src/math
        src/objects
        src/renderer
        src/shader
        src/texture
        src/util
        src/window)
add_executable(billiards src/main.cpp ${SOURCE_FILES})
target_link_libraries(billiards GL GLEW glfw m assimp)
