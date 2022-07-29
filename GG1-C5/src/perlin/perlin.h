/**
 * @file perlin.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Generates perlin noise in a specified number of dimensions
 * @version 0.1
 * @date 2022-07-22
 */

#ifndef PERLIN_H
#define PERLIN_H

#include <iostream>
using std::cout;

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cspline/cspline.h"

/*
From GG1-C5.2

At each point in space (i, j, k) that has integer coordinates, assign a value
 of zero and a pseudo-random gradient that is hashed from (i, j, k).

Define the coordinates of (x, y, z) as an integer value plus a fractional 
 remainder: (x, y, z) = (i + u, j + v, k + w). Consider the eight corners 
 of the unit cube surrounding this point: 
 (i, j, k), (i + 1, j, k), . . . (i + 1, j + 1, k + 1).

Fit a Hermite spline through these eight points, and evaluate this spline 
 at (x, y, z), using u, v, and w as interpolants. If we use a table lookup 
 to predefine the Hermite cubic blending function 3t^2 - 2t^2, then this 
 interpolation requires only seven scalar linear interpolations: 
 for example, four in x, followed by two in y, followed by one in z.
*/

class Perlin {
    public:
        Perlin();
        ~Perlin();

        float at(float x, float y, float z);
        float at(glm::vec3 p);

        static glm::vec3 hashGradient(glm::vec3 p);

    private:
        static float hashRand(float p);
        static float hashRand(glm::vec2 p);
        static float hashRand(glm::vec3 p);


};


#endif