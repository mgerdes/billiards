#version 330 core

struct Material {
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
    sampler2D texture;
};

struct Light {
    vec3 position;
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture_coords;

uniform Material material;
uniform Light light;
uniform vec3 camera_position;

out vec4 color;

void main () {
    // Ambient
    vec3 ambient_color = light.ambient_color * material.ambient_color;

    // Diffuse
    vec3 norm = normalize(frag_normal);
    vec3 light_direction = normalize(light.position - frag_position);
    float d = max(dot(norm, light_direction), 0.0);
    vec3 diffuse_color = d * light.diffuse_color * material.diffuse_color;

    // Specular
    vec3 view_direction = normalize(camera_position - frag_position);
    vec3 reflected_direction = reflect(-light_direction, norm);
    float p = pow(max(dot(view_direction, reflected_direction), 0.0), material.shininess);
    vec3 specular_color = p * light.specular_color * material.specular_color;

    vec4 texel = texture(material.texture, frag_texture_coords);

    color = vec4(ambient_color + diffuse_color + specular_color, 1.0) + texel;
}
