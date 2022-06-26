#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

vec4 pointLight(){
	
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0f;
	float b = 2.0f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);


	//Ambient Lighting
	float ambient = 0.2f;

	//Diffuse Lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//Specular Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) +  texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directLight(){

	//Ambient Lighting
	float ambient = 0.2f;

	//Diffuse Lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f,1.0f,0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//Specular Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) +  texture(specular0, texCoord).r * specular) * lightColor;
}
vec4 spotLight(){

	float outerCone = 0.9f;
	float innerCone = 0.95f;
	
	//Ambient Lighting
	float ambient = 0.2f;

	//Diffuse Lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//Specular Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f,-1.0f,0.0f) , -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) +  texture(specular0, texCoord).r * specular * inten) * lightColor;
}
float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth){
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}
float logisticDepth(float depth, float steepness, float offset){
	float zVal = linearizeDepth(depth);
	return (1/(1+exp(-steepness * (zVal - offset))));
}

void main()
{
	
	float depth = logisticDepth(gl_FragCoord.z, 0.5f, 5.0f);
	FragColor = directLight() * (1.0f-depth) + vec4(depth * vec3(0.85f,0.85f,0.90f), 1.0f);
	
}