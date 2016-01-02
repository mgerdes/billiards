#version 330 core

layout(location=0) in vec3 vert_position;
layout(location=1) in vec3 vert_normal;
layout(location=2) in vec2 vert_texture_coords;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture_coords;

void main () {
    vec4 normal_temp = transpose(inverse(model_mat)) * vec4(vert_normal, 0.0);
    vec4 position_temp = model_mat * vec4(vert_position, 1.0);

    frag_position = position_temp.xyz;
    frag_normal = normal_temp.xyz;
    frag_texture_coords = vert_texture_coords;

    gl_Position = proj_mat * view_mat * model_mat * vec4(vert_position, 1.0);
}