#version 330 core

layout(location=0) in vec3 vert_position;
layout(location=1) in vec3 vert_normal;
layout(location=2) in vec2 vert_texture_coord;

uniform mat4 proj_mat;
uniform mat4 view_mat;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture_coord;

void main () {
    frag_position = vert_position;
    frag_normal = vert_normal;
    frag_texture_coord = vert_texture_coord;

    gl_Position = proj_mat * view_mat * vec4(vert_position, 1.0);
}
