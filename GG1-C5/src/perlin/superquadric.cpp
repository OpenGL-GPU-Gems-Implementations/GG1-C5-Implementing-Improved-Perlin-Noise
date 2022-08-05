/**
 * @file superquadric.cpp
 * @author Eron Ristich (eron@ristich.com)
 * @brief Functions for generating the mesh of a noise-displaced cube and superquadric
 * @version 0.1
 * @date 2022-07-26
 */

#include "superquadric.h"

MiniMesh::MiniMesh(vector<float>* vertices, vector<unsigned int>* strips, int xns, int yns, int zns, int xnvps, int ynvps, int znvps) : vertices(vertices), strips(strips), xns(xns), yns(yns), zns(zns), xnvps(xnvps), ynvps(ynvps), znvps(znvps) {
    // assumes sdl has been initiated, and that there is a valid gl context
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                vertices->size() * sizeof(float),       // size of vertices buffer
                &(*vertices)[0],                        // pointer to first element (C++ vectors are contiguous so order is preserved [&v[n] == &v[0] + n for all 0 <= n < v.size()])
                GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                strips->size() * sizeof(unsigned int),  // size of strips buffer
                &(*strips)[0],                          // pointer to first element (see above for explanation)
                GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

MiniMesh::~MiniMesh() {
    delete[] vertices;
    delete[] strips;
}

void MiniMesh::draw() {
    // assumes sdl has been initiated, and that there is a valid gl context
    glBindVertexArray(VAO);

    for (int i = 0; i < 2*xns; i ++) {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                    xnvps, // number of indices to render
                    GL_UNSIGNED_INT,     // index data type
                    (void*)(sizeof(unsigned int)
                             * xnvps
                             * i)); // offset to starting index
    }
    for (int i = 2*xns; i < 2*(xns+yns); i ++) {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                    ynvps, // number of indices to render
                    GL_UNSIGNED_INT,     // index data type
                    (void*)(sizeof(unsigned int)
                             * xnvps
                             * 2 * xns +
                            sizeof(unsigned int)
                             * ynvps
                             * i)); // offset to starting index
    }
    for (int i = 2*(xns+yns); i < 2*(xns+yns+zns); i ++) {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                    znvps, // number of indices to render
                    GL_UNSIGNED_INT,     // index data type
                    (void*)(sizeof(unsigned int)
                             * xnvps
                             * 2 * xns +
                            sizeof(unsigned int)
                             * ynvps
                             * 2 * yns +
                            sizeof(unsigned int)
                             * znvps
                             * i)); // offset to starting index
    }
    
}

// returns a signed 1 for each dimension that lies on a face/edge
glm::vec3 onEdge(int px, int py, int pz, int x, int y, int z) {
    int resx = 0; int resy = 0; int resz = 0;
    
    if (px == x) {
        resx = 1;
    } else if (px == 0) {
        resx = -1;
    }

    if (py == y) {
        resy = 1;
    } else if (py == 0) {
        resy = -1;
    }

    if (pz == y) {
        resz = 1;
    } else if (pz == 0) {
        resz = -1;
    }
    
    return glm::vec3(resx, resy, resz);
}

// generates a cube in the first octant with a corner at the origin. use translation/scaling functions to change relative scale
MiniMesh* genCube(int x, int y, int z) {
    Perlin* perlin = new Perlin();
    
    // generate vertices in order +-x, +-y, +-z
    // there should be 2yz x vertices, 2xz y vertices, and 2xy z vertices
    vector<float>* vertices = new vector<float>();
    
    // I am adding duplicates of every edge/corner to the set of vertices for ease of computation
    // generate vertices
    // +- x
    for (int i = 0; i <= 1; i ++) {
        int xcoord = i*(x-1);
        for (int j = 0; j < y; j ++) {
            int ycoord = j;
            for (int k = 0; k < z; k ++) {
                int zcoord = k;

                glm::vec3 pnt = glm::vec3(xcoord, ycoord, zcoord);
                glm::vec3 dir = onEdge(xcoord, ycoord, zcoord, x-1, y-1, z-1)*2.0f;
                float perlinRes = 2*perlin->at(pnt * 0.13257f);
                pnt = pnt + dir*perlinRes;

                vertices->push_back(pnt.x);
                vertices->push_back(pnt.y);
                vertices->push_back(pnt.z);
            }
        }
    }

    // +- y
    for (int i = 0; i <= 1; i ++) {
        int ycoord = i*(y-1);
        for (int j = 0; j < x; j ++) {
            int xcoord = j;
            for (int k = 0; k < z; k ++) {
                int zcoord = k;

                glm::vec3 pnt = glm::vec3(xcoord, ycoord, zcoord);
                glm::vec3 dir = onEdge(xcoord, ycoord, zcoord, x-1, y-1, z-1)*2.0f;
                float perlinRes = perlin->at(pnt * 0.13257f);
                pnt = pnt + dir*perlinRes;

                vertices->push_back(pnt.x);
                vertices->push_back(pnt.y);
                vertices->push_back(pnt.z);
            }
        }
    }

    // +- z
    for (int i = 0; i <= 1; i ++) {
        int zcoord = i*(z-1);
        for (int j = 0; j < x; j ++) {
            int xcoord = j;
            for (int k = 0; k < y; k ++) {
                int ycoord = k;

                glm::vec3 pnt = glm::vec3(xcoord, ycoord, zcoord);
                glm::vec3 dir = onEdge(xcoord, ycoord, zcoord, x-1, y-1, z-1)*2.0f;
                float perlinRes = perlin->at(pnt * 0.13257f);
                pnt = pnt + dir*perlinRes;

                vertices->push_back(pnt.x);
                vertices->push_back(pnt.y);
                vertices->push_back(pnt.z);
            }
        }
    }

    // generate indices in order +-x, +-y, +-z
    // [ 2 * xnvps * xns, 2 * ynvps * yns, 2 * znvps * zns ]
    /* 
    ns - number of strips
    nvps - number of vertices per strip

    x is y by z: generated across z's, down y's
        xns = y-1
        xnvps = z*2
    y is x by z: generated across z's, down x's
        yns = x-1
        ynvps = z*2
    z is x by y: generated across y's, down x's
        zns = x-1
        znvps = y*2
    */
    // this can be optimized (maringally) by using the minimum dimension of each face as the number of strips for that face 
    // note that these are the counts for a single face of that dimension (notably, the opposing face is symmetric, and thus multiplying the given values by 2 is sufficient)
    int xns = y-1; int xnvps = z*2;
    int yns = x-1; int ynvps = z*2;
    int zns = x-1; int znvps = y*2;

    vector<unsigned int>* strips = new vector<unsigned int>();

    // index supplement, for +-x, indB is 0, for +-y indB is 2yz, for +-z indB is 2z(x+y)
    int indB = 0;

    // +- x
    for (int i = 0; i <= 1; i ++) { // +-
        for (int j = 0; j < xns; j ++) { // number of strips
            for (int k = 0; k < xnvps/2; k ++) { // half of the vertices in strip
                // vertex value is at indB + current row * width + current column + yz*i
                // secondary vertex is at indB + (current row + 1) * width + current column
                strips->push_back(indB + j*(xnvps/2) + k + i*y*z);
                strips->push_back(indB + (j+1)*(xnvps/2) + k + i*y*z);
            }
        }
    }

    // +- y
    indB = 2*y*z;
    for (int i = 0; i <= 1; i ++) { // +-
        for (int j = 0; j < yns; j ++) { // number of strips
            for (int k = 0; k < ynvps/2; k ++) { // half of the vertices in strip
                // vertex value is at indB + current row * width + current column + xz*i
                // secondary vertex is at indB + (current row + 1) * width + current column
                strips->push_back(indB + j*(ynvps/2) + k + i*x*z);
                strips->push_back(indB + (j+1)*(ynvps/2) + k + i*x*z);
            }
        }
    }

    // +- z
    indB = 2*z*(x+y);
    for (int i = 0; i <= 1; i ++) { // +-
        for (int j = 0; j < zns; j ++) { // number of strips
            for (int k = 0; k < znvps/2; k ++) { // half of the vertices in strip
                // vertex value is at indB + current row * width + current column + xy*i
                // secondary vertex is at indB + (current row + 1) * width + current column
                strips->push_back(indB + j*(znvps/2) + k + i*x*y);
                strips->push_back(indB + (j+1)*(znvps/2) + k + i*x*y);
            }
        }
    }
    
    MiniMesh* miniMesh = new MiniMesh(vertices, strips, xns, yns, zns, xnvps, ynvps, znvps);

    delete perlin;
    return miniMesh;
}

// superquadric
glm::vec3 projectOnUnitSuperquadric(int power, glm::vec3 point) {
    // project point onto unit sphere (normalize point vector)
    point = glm::normalize(point);

    // compute displacement constant
    float tx = pow(abs(point.x), power);
    float ty = pow(abs(point.y), power);
    float tz = pow(abs(point.z), power);
    float a = pow(1/(tx+ty+tz), 1.0f / power);
    
    return point*a;
}

int Superquadric::indexForEdge(Lookup& lookup, vector<glm::vec3>& vertices, int first, int second) {
    Lookup::key_type key(first, second);
    if (key.first > key.second)
        std::swap(key.first, key.second);
    
    auto inserted = lookup.insert({key, vertices.size()});
    if (inserted.second) {
        auto& edge0 = vertices[first];
        auto& edge1 = vertices[second];
        auto point = normalize(edge0 + edge1);
        vertices.push_back(point);
    }
    
    return inserted.first->second;
}

Superquadric::Superquadric(int d, int power) {
    vertices = new vector<float>();
    indices = new vector<unsigned int>();

    assorted = new vector<glm::vec3>();
    triangles = new vector<Triangle>();

    genMesh(d, power);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                vertices->size() * sizeof(float),       // size of vertices buffer
                &(*vertices)[0],                        // pointer to first element (C++ vectors are contiguous so order is preserved [&v[n] == &v[0] + n for all 0 <= n < v.size()])
                GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                indices->size() * sizeof(unsigned int),  // size of indices buffer
                &(*indices)[0],                          // pointer to first element (see above for explanation)
                GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

Superquadric::~Superquadric() {

}

void Superquadric::subdivide() {
    Lookup lookup;
    vector<Triangle> result;
    
    for (auto&& each:*triangles) {
        std::array<int, 3> mid;
        for (int edge = 0; edge < 3; edge ++) {
            mid[edge] = indexForEdge(lookup, *assorted, each.indices[edge], each.indices[(edge+1)%3]);
        }
    
        result.push_back({each.indices[0], mid[0], mid[2]});
        result.push_back({each.indices[1], mid[1], mid[0]});
        result.push_back({each.indices[2], mid[2], mid[1]});
        result.push_back({mid[0], mid[1], mid[2]});
    }
    
    *triangles = result;
}

// implementing algorithm from https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
void Superquadric::genMesh(int detail, int power) {
    *assorted = icosahedron::vertices;
    *triangles = icosahedron::triangles;
    
    for (int i = 0; i < detail; i ++)
        subdivide();

    Perlin perlin = Perlin();

    // gl ready vectors
    for (auto&& each:*assorted) {
        glm::vec3 temp = projectOnUnitSuperquadric(power, each);
        temp += normalize(temp) * perlin.at(temp) * 0.25f;
        vertices->push_back(temp.x);
        vertices->push_back(temp.y);
        vertices->push_back(temp.z);
    }

    for (auto&& each:*triangles) {
        indices->push_back(each.indices[0]);
        indices->push_back(each.indices[1]);
        indices->push_back(each.indices[2]);
    }
}

void Superquadric::draw() {
    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,      // mode
        indices->size(),   // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
    );
}