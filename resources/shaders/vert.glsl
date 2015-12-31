#version 330 core

layout(location=0) in vec3 vert_position;

void main () {
    gl_Position = vec4(vert_position, 1.0);
}