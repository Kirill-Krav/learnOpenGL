#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 inverseModel;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 fragPos;
out vec3 normal;
out vec3 fraglightPos;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	fragPos = vec3(view * model * vec4(aPos, 1.0));
	normal = mat3(transpose(inverseModel)) * aNormal;
	fraglightPos = vec3(view * vec4(lightPos, 1.0f));
}