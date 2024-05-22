#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 inverseModel;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

void main(){
	fragPos = vec3(model * vec4(aPos, 1.0));

	gl_Position = projection * view * vec4(fragPos, 1.0f);
	
	normal = mat3(transpose(inverseModel)) * aNormal;

	texCoords = aTexCoords;
}