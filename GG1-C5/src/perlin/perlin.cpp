/**
 * @file perlin.cpp
 * @author Eron Ristich (eron@ristich.com)
 * @brief Generates perlin noise in a specified number of dimensions
 * @version 0.1
 * @date 2022-07-22
 */

#include "perlin.h"

Perlin::Perlin() {
    
}

Perlin::~Perlin() {

}

float Perlin::at(float x, float y, float z) {
    return at(glm::vec3(x, y, z));
}

float Perlin::at(glm::vec3 p) {
    glm::vec3 p000 = glm::floor(p);
    glm::vec3 p001 = p000 + glm::vec3(0.,0.,1.);
    glm::vec3 p010 = p000 + glm::vec3(0.,1.,0.);
    glm::vec3 p100 = p000 + glm::vec3(1.,0.,0.);
    glm::vec3 p011 = p000 + glm::vec3(0.,1.,1.);
    glm::vec3 p101 = p000 + glm::vec3(1.,0.,1.);
    glm::vec3 p110 = p000 + glm::vec3(1.,1.,0.);
    glm::vec3 p111 = p000 + glm::vec3(1.,1.,1.);
    
    glm::vec3 intrp = glm::fract(p);
    
    float v000 = glm::dot(hashGradient(p000), p-p000);
    float v001 = glm::dot(hashGradient(p001), p-p001);
    float v010 = glm::dot(hashGradient(p010), p-p010);
    float v100 = glm::dot(hashGradient(p100), p-p100);
    float v011 = glm::dot(hashGradient(p011), p-p011);
    float v101 = glm::dot(hashGradient(p101), p-p101);
    float v110 = glm::dot(hashGradient(p110), p-p110);
    float v111 = glm::dot(hashGradient(p111), p-p111);
    
    float x1 = Hermite::interpolate(intrp.x, v000, v100);
    float x2 = Hermite::interpolate(intrp.x, v010, v110);
    float x3 = Hermite::interpolate(intrp.x, v001, v101);
    float x4 = Hermite::interpolate(intrp.x, v011, v111);
    
    float y1 = Hermite::interpolate(intrp.y, x1, x2);
    float y2 = Hermite::interpolate(intrp.y, x3, x4);
    
    float z1 = Hermite::interpolate(intrp.z, y1, y2);
    
    return z1;
}

glm::vec3 Perlin::hashGradient(glm::vec3 p) {
    float theta = 2.0*3.1415*hashRand(p);
    float phi = acos(2.0*hashRand(p)-1.0);
    return glm::vec3(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

float Perlin::hashRand(float p) {
    double intpart;
    return abs(modf(sin(p*91.3458)*47453.5453, &intpart));
}

float Perlin::hashRand(glm::vec2 p) {
    double intpart;
    float temp = glm::dot(p, glm::vec2(12.9898,78.233));
    return abs(modf(sin(temp)*43758.5453, &intpart));
}

float Perlin::hashRand(glm::vec3 p) {
    return hashRand(glm::vec2(p.x, p.y) + hashRand(p.z));
}