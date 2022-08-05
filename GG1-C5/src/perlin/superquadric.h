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

#include <math.h>
#include <utility>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "perlin.h"

// basically only for the generated cube/superquadric
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
MiniMesh* genCube(int x, int y, int z);

// golden ratio
const double GOLDEN_RATIO = (1.0 + sqrt(5.0))/2.0;

// storage structs
struct Triangle {
    int indices[3];
};

// hard coded icosahedron
#define X .525731112119133606
#define Z .850650808352039932
#define PI 3.14159265

namespace icosahedron {
    static const vector<glm::vec3> vertices = {
        glm::vec3(-X, 0, Z), glm::vec3(X, 0, Z), glm::vec3(-X, 0, -Z), glm::vec3(X, 0, -Z),
        glm::vec3(0, Z, X), glm::vec3(0, Z, -X), glm::vec3(0, -Z, X), glm::vec3(0, -Z, -X),
        glm::vec3(Z, X, 0), glm::vec3(-Z, X, 0), glm::vec3(Z, -X, 0), glm::vec3(-Z, -X, 0)
    };

    static const vector<Triangle> triangles = {
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
        {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
        {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
        {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
    };
}

// projects any point to a point on a unit cubic superquadric of a given power
// defined by |x|^p + |y|^p + ... = 1
glm::vec3 projectOnUnitSuperquadric(int power, glm::vec3 point);

// vertex/edge lookup functions
using Lookup = std::map<std::pair<int, int>, int>; // from schneide.blog

// superquadric class
// renders using GL triangles but could probably be faster if using GL strip (fibonnaci lattice?)
// uses recursion on a hard-coded icosahedron to generate mesh 
class Superquadric {
    public:
        // integer relative dimensions of triangles on superquadric
        Superquadric(int d, int power);
        ~Superquadric();
        
        // generate superquadric (given depth of recursion as a "detail" parameter)
        void genMesh(int detail, int power);

        // draws the mesh
        void draw();

    private:
        GLuint VAO, VBO, EBO;

        vector<float>* vertices;
        vector<unsigned int>* indices;

        vector<glm::vec3>* assorted;
        vector<Triangle>* triangles;

        // one iteration of subdivision
        void subdivide();
        int indexForEdge(Lookup& lookup, vector<glm::vec3>& vertices, int first, int second);
};


#endif