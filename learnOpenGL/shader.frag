#version 460 core

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

out vec4 FragColor;

void main(){
   FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);// * vec4(ourColor, 1.0f);
}