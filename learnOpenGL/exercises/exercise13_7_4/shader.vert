#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 inverseModel;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

out vec3 lightingColor;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	
	vec3 position = vec3(model * vec4(aPos, 1.0f));
	vec3 normal = mat3(transpose(inverseModel)) * aNormal;

	//ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - position);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 1.0f;
	vec3 viewDir = normalize(viewPos - position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	lightingColor = ambient + diffuse + specular;
}