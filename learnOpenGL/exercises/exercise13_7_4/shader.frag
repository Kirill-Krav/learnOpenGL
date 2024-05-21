#version 460 core

in vec3 lightingColor; 

uniform vec3 objectColor;

out vec4 fragColor;

void main(){
	fragColor = vec4(lightingColor * objectColor, 1.0);
}