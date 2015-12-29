#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_utils.h"
#include "camera.h"
#include "maths.h"
#include "mesh.h"
#include "model.h"
#include "billiards_game.h"

Camera* camera;

void handle_input(BilliardsGame* game) {
    double current_seconds = glfwGetTime();
    static double last_key_press;
}

int main() {
    Window* window = create_window("opengl", 1000, 1000);

    camera = create_default_camera();

    GLuint shader_program = create_shader_program("shaders/frag.glsl", "shaders/vert.glsl");

	GLint proj_mat_location = glGetUniformLocation(shader_program, "proj_mat");
	GLint view_mat_location = glGetUniformLocation(shader_program, "view_mat");

    Mat* proj_mat = create_perspective_mat(67.0, 1.0, 0.1, 1000.0);
    Mat* view_mat = mat_times_mat(create_look_at_mat(camera->position, camera->center, camera->up), create_translation_mat(-0.15, -0.15, 0.0));

	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat->m);
    glUniformMatrix4fv(view_mat_location,1, GL_FALSE, view_mat->m);

    BilliardsGame* billiards_game = create_billiards_game(shader_program);

    while (!glfwWindowShouldClose(window->glfwWindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        handle_input(billiards_game);

        Mat* view_mat = mat_times_mat(create_look_at_mat(camera->position, camera->center, camera->up), create_translation_mat(-0.15, -0.15, 0.0));
        glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat->m);

        draw_billiards_game(billiards_game);

        glfwPollEvents();
        glfwSwapBuffers(window->glfwWindow);
    }

    glfwTerminate();
}
