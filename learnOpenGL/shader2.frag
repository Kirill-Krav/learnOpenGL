#version 460 core

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

out vec4 FragColor;

void main()
{    
    //vec3 I = normalize(position - cameraPos);
    //vec3 R = reflect(I, normalize(normal));
    //FragColor = vec4(texture(skybox, R).rgb, 1.0f);
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(position - cameraPos);
    vec3 R = refract(I, normalize(normal), ratio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}