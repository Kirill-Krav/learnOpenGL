#version 460 core

in vec2 texCoords;

uniform sampler2D texture1;

out vec4 FragColor;

void main()
{    
    FragColor = texture(texture1, texCoords);
}