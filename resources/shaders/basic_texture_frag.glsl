#version 330 core

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture_coord;

uniform sampler2D tex;

out vec4 color;

void main () {
    vec3 light_position = vec3(1.0, 1.0, 1.0);

    float kd = max(dot(light_position, frag_normal), 0.0);

    vec4 texel = texture(tex, frag_texture_coord);
    color = vec4(0.1, 0.1, 0.1, 1.0) + texel;
    color *= kd;
}
