#version 430 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objColor;

uniform int iFrame;

// implementing the same perlin noise as in Perlin C++ class (perlin.cpp)
// for smoother bump mapping
float rand(float co){ return fract(sin(co*(91.3458)) * 47453.5453); }
float rand(vec2 co){ return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }
float rand(vec3 co){ return rand(co.xy+rand(co.z)); }

vec3 randGradient(vec3 p) {
    float theta = 2.0*3.1415*rand(p+1.);
    float phi = acos(2.0*rand(p)-1.0);
    return vec3(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

// simple hermite
float simple(float t, float p0, float p1) {
    //return (-2.*t*t*t+3.*t*t)*(p1-p0)+p0; // 3rd order interpolant
    return (6*t*t*t*t*t-15*t*t*t*t+10*t*t*t)*(p1 - p0) + p0; // 5th order interpolant
}

float perlin(vec3 p) {
    vec3 p000 = floor(p);
    vec3 p001 = p000 + vec3(0.,0.,1.);
    vec3 p010 = p000 + vec3(0.,1.,0.);
    vec3 p100 = p000 + vec3(1.,0.,0.);
    vec3 p011 = p000 + vec3(0.,1.,1.);
    vec3 p101 = p000 + vec3(1.,0.,1.);
    vec3 p110 = p000 + vec3(1.,1.,0.);
    vec3 p111 = p000 + vec3(1.,1.,1.);
    
    vec3 intrp = fract(p);
    
    float v000 = dot(randGradient(p000), p-p000);
    float v001 = dot(randGradient(p001), p-p001);
    float v010 = dot(randGradient(p010), p-p010);
    float v100 = dot(randGradient(p100), p-p100);
    float v011 = dot(randGradient(p011), p-p011);
    float v101 = dot(randGradient(p101), p-p101);
    float v110 = dot(randGradient(p110), p-p110);
    float v111 = dot(randGradient(p111), p-p111);
    
    float x1 = simple(intrp.x, v000, v100);
    float x2 = simple(intrp.x, v010, v110);
    float x3 = simple(intrp.x, v001, v101);
    float x4 = simple(intrp.x, v011, v111);
    
    float y1 = simple(intrp.y, x1, x2);
    float y2 = simple(intrp.y, x3, x4);
    
    float z1 = simple(intrp.z, y1, y2);
    
    return z1;
}

// octave noise
float noise(vec3 p, float v) {
    return perlin(p*v);
}

// STRIPES TEXTURE (GOOD FOR MAKING MARBLE) 
float stripes(float x, float f) {
    float t = .5 + .5 * sin(f * 2*3.1415 * x);
    return t * t - .5;
} 

// TURBULENCE TEXTURE 
float turbulence(vec3 p, float f) {
    float t = -.5;
    for ( ; f <= 128 ; f *= 2) {
        t += abs(noise(p, f) / f);   
    }
    return t;
}

// .03 * noise(p, 8); //LUMPY 
// .01 * stripes(p.x + 2 * turbulence(p, 1), 1.6);  //MARBLED 
//-.10 * turbulence(p, 1);                       //CRINKLED 

float e = 0.01;
float F(vec3 p) {
    return .03 * noise(p, 8);
    //return .01 * stripes(p.x + 2 * turbulence(p, 1), 1.6);
    //return -.1 * turbulence(p, 1);
}

vec3 gendF(vec3 p) {
    float F0 = F(p);
    float Fx = F(vec3(p.x+e, p.y, p.z));
    float Fy = F(vec3(p.x, p.y+e, p.z));
    float Fz = F(vec3(p.x, p.y, p.z+e));

    return vec3((Fx-F0)/e, (Fy-F0)/e, (Fz-F0)/e);
}

void main() {
    // compute normal
    vec3 dx = dFdx(FragPos);
    vec3 dy = dFdy(FragPos);
    vec3 N = -normalize(cross(dx, dy));
    vec3 dF = gendF(FragPos);

    N = normalize(N + dF);
    
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
    vec3 reflectDir = reflect(lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0);
} 