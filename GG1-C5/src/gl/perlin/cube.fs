#version 430 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objColor;

void main() {
    // compute normal
    vec3 dx = dFdx(FragPos);
    vec3 dy = dFdy(FragPos);
    vec3 N = -normalize(cross(dx, dy));
    
    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(N);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0);
} 