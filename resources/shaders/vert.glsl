#version 330 core

layout(location=0) in vec3 vert_position;
layout(location=1) in vec3 vert_normal;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec3 frag_position;
out vec3 frag_normal;

void main () {
    vec4 temp = transpose(inverse(model_mat)) * vec4(vert_normal, 0.0);

    frag_position = vert_position;
    frag_normal = temp.xyz;

    gl_Position = proj_mat * view_mat * model_mat * vec4(vert_position, 1.0);
}