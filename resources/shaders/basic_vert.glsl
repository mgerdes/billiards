#version 330 core

layout(location=0) in vec3 vert_position;

uniform mat4 proj_mat;
uniform mat4 view_mat;

void main () {
    gl_Position = proj_mat * view_mat * vec4(vert_position, 1.0);
}
