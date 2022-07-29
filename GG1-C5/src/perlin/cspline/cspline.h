/**
 * @file cspline.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Collection of spline functions
 * @version 0.1
 * @date 2022-07-22
 */

#ifndef CSPLINE_H
#define CSPLINE_H

#include <iostream>
using std::cout;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Spline {
    public:
        Spline(float** inp, float* t, int n, int d);
        ~Spline() {}

        //empty, as Spline should not be used as a spline
        virtual float* p(float t) {return NULL;}

    protected:
        // input data
        float** inp;
        float* tp;
        
        // n - number of points
        // d - number of dimensions
        int n, d;
        // t - tangent
        int tn, td;
};

// used for tangent selection
enum HermiteTangents {THREE_POINT, CATMULL_ROM, KOCHANEK_BARTELS, CARDINAL};

class Hermite : public Spline {
    public:
        Hermite(float** inp, float* t, int n, int d, HermiteTangents type, float tension);
        ~Hermite();

        float* p(float t) override;

        // hermite basis functions along the interval t=[0, 1]
        static float h00(float t);
        static float h10(float t);
        static float h01(float t);
        static float h11(float t);

        // interpolate along t=[0, 1], from p0 to p1 with endpoint tangents of 0
        static float interpolate(float t, float p0, float p1);


    private:
        // list of tangents
        float** tang;

        HermiteTangents type;
        void genTangents_threePoint();
        void genTangents_catmullRom();
        void genTangents_kochanekBartels();
        void genTangents_cardinal(float tension);
};

// functionally equivalent to the Hermite Spline
class Bezier : public Spline {

};

#endif