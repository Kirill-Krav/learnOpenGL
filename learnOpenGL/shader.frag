#version 460 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 direction;
	vec3 position;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 fragColor;

void main(){
	vec3 lightDir = normalize(light.position - fragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intencity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	
	//amnient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	ambient *= intencity * attenuation;

	//diffuse
	vec3 norm = normalize(normal);
		
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	diffuse *= intencity * attenuation;

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	specular *= intencity * attenuation;

	fragColor = vec4(ambient + diffuse + specular, 1.0f);

	
}