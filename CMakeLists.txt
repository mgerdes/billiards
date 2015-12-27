cmake_minimum_required(VERSION 3.3)
project(billiards)

set(SOURCE_FILES
        image_reader/stb_image.h
        maths/maths.c
        maths/maths.h
        objects/mesh.c
        objects/mesh.h
        objects/model.c
        objects/model.h
        utils/camera.c
        utils/camera.h
        utils/gl_utils.c
        utils/gl_utils.h
        simulation/billiards_game.h
        simulation/billliards_game.c
        main.c)

include_directories(image_reader maths objects simulation utils)

add_executable(billiards ${SOURCE_FILES})

target_link_libraries(billiards GL GLEW glfw m assimp)
