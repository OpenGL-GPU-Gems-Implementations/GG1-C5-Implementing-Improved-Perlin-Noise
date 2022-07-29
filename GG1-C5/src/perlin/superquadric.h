/**
 * @file superquadric.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Functions for generating the mesh of a noise-displaced superquadric 
 * @version 0.1
 * @date 2022-07-26
 */

#ifndef SUPERQUADRIC_H
#define SUPERQUADRIC_H

#include <vector>
using std::vector;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "perlin.h"

// basically only for the superquadric
class MiniMesh {
    public:
        MiniMesh(vector<float>* vertices, vector<unsigned int>* strips, int xns, int yns, int zns, int xnvps, int ynvps, int znvps);
        ~MiniMesh();

        // maybe code a "draw" function, so a minimesh can store its own shader and draw itself, etc.
        void draw();

    private:
        GLuint VAO, VBO, EBO;

        vector<float>* vertices;
        vector<unsigned int>* strips;
        int xns, yns, zns;
        int xnvps, ynvps, znvps;


};

// determines if a point (px, py, pz) is on an edge/face of a box with dimensions x, y, z, in the 1st octant
glm::vec3 onEdge(int px, int py, int pz, int x, int y, int z);

// generates mesh triangles for a superquadric. for scaling/translation, use related matrix functions
// accepts integer dimensions (resolution of cubics in each direction)
MiniMesh* genSuperquadric(int x, int y, int z);

#endif