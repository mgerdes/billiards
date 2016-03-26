#version 330 core

in vec2 frag_texture_coord;

uniform sampler2D tex;

out vec4 color;

void main () {
    vec4 texel = texture(tex, frag_texture_coord);
    color = vec4(0.1, 0.1, 0.1, 1.0) + texel;
}
