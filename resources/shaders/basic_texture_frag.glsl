#version 330 core

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture_coord;

uniform sampler2D tex;

out vec4 color;

void main () {
    vec3 light_position1 = vec3(0.0, 1.0, 2.0);
    vec3 light_position2 = vec3(0.0, 1.0, -2.0);
    vec3 light_position3 = vec3(2.0, 1.0, 0.0);
    vec3 light_position4 = vec3(-2.0, 1.0, 0.0);
    vec3 light_position5 = vec3(2.0, 1.0, 2.0);
    vec3 light_position6 = vec3(-2.0, 1.0, -2.0);
    vec3 light_position7 = vec3(2.0, 1.0, 2.0);
    vec3 light_position8 = vec3(-2.0, 1.0, -2.0);

    float kd = max(dot(light_position1, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position2, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position3, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position4, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position5, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position6, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position7, frag_normal), 0.0) * 0.12;
    kd += max(dot(light_position8, frag_normal), 0.0) * 0.12;

    vec4 texel = texture(tex, frag_texture_coord);
    color = vec4(0.1, 0.1, 0.1, 1.0) + texel * 0.9;
    color *= kd;
}
