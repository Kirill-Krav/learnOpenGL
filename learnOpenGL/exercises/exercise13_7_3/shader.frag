#version 460 core

in vec3 normal;
in vec3 fragPos;
in vec3 fraglightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 fragColor;

void main(){
	//amnient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(fraglightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	fragColor = vec4(result, 1.0f);
}