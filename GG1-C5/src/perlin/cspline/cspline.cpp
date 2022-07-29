/**
 * @file cspline.cpp
 * @author Eron Ristich (eron@ristich.com)
 * @brief Collection of spline functions
 * @version 0.1
 * @date 2022-07-22
 */

#include "cspline.h"

Spline::Spline(float** inp, float* t, int n, int d) : inp(inp), tp(t), n(n), d(d) {

}

float* Hermite::p(float t) {
    throw std::logic_error("Function not yet implemented");
    //float* res = new float[d];
    
    switch (type) {
        case THREE_POINT:
            
            break;
        
        case CARDINAL:
            if (t < tp[1] || t > tp[tn]) {
                throw std::runtime_error("t outside valid range");
            }
            break;

        default:
            throw std::logic_error("Function not yet implemented");
            break;
    }


    return NULL;
}

// where inp is a set of control points along some function p(t). the set of t corresponding to each control point is defined by the list t (tp). the set of control points should be in order
Hermite::Hermite(float** inp, float* t, int n, int d, HermiteTangents type, float tension=0.5f) : Spline(inp, t, n, d), type(type) {
    switch (type) {
        case THREE_POINT:
            genTangents_threePoint();
            break;
        
        case CATMULL_ROM:
            genTangents_catmullRom();
            break;
        
        case KOCHANEK_BARTELS:
            genTangents_kochanekBartels();
            break;

        case CARDINAL:
            genTangents_cardinal(tension);
            break;
        
        default:
            throw std::runtime_error("Invalid Hermite Tangent type");
            break;
    }

    cout << "{";
    for (int i = 0; i < tn; i ++) {
        cout << "{";
        for (int j = 0; j < td; j ++) {
            cout << tang[i][j];
            if (j < td-1)
                cout << ", ";
        }
        cout << "}";
        if (i < tn-1)
            cout << ", ";
    }
    cout << "}";
}

Hermite::~Hermite() {
    for (int i = 0; i < tn; i ++) {
        delete[] tang[i];
    }
    delete[] tang;
}

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Finite_difference
void Hermite::genTangents_threePoint() {
    if (n < 3)
        throw std::runtime_error("Control point set must be a minimum of 3 elements large in order to implement Hermite Spline three-point tangents");

    // setup tangent array
    tn = n;
    td = d;
    tang = new float*[tn];
    for (int i = 0; i < tn; i ++) {
        tang[i] = new float[td];
    }

    // endpoints
    for (int i = 0; i < d; i ++) {
        tang[0][i] = (inp[1][i] - inp[0][i])/(tp[1] - tp[0]);
        tang[n-1][i] = (inp[n-1][i] - inp[n-2][i])/(tp[n-1] - tp[n-2]);
    }


    // midpoints
    for (int i = 1; i < n-1; i ++) {
        for (int j = 0; j < d; j ++) {
            tang[i][j] = 0.5 * ((inp[i+1][j] - inp[i][j])/(tp[i+1] - tp[i]) + (inp[i][j] - inp[i-1][j])/(tp[i] - tp[i-1]));
        }
    }
}

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline
void Hermite::genTangents_catmullRom() {
    throw std::logic_error("Function not yet implemented");
}

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Kochanek%E2%80%93Bartels_spline
void Hermite::genTangents_kochanekBartels() {
    throw std::logic_error("Function not yet implemented");
}

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
void Hermite::genTangents_cardinal(float tension) {
    if (n < 3)
        throw std::runtime_error("Control point set must be a minimum of 3 elements large in order to implement Hermite Spline cardinal tangents");

    // setup tangent array
    tn = n-2;
    td = d;
    tang = new float*[tn];
    for (int i = 0; i < tn; i ++) {
        tang[i] = new float[td];
    }

    // midpoints
    for (int i = 1; i < n-1; i ++) {
        for (int j = 0; j < d; j ++) {
            tang[i-1][j] = (1.0f - tension) * ((inp[i+1][j] - inp[i-1][j])/(tp[i+1] - tp[i-1]));
        }
    }
}

float Hermite::interpolate(float t, float p0, float p1) {
    // 3rd degree interpolation
    //return (-2*t*t*t + 3*t*t)*(p1 - p0) + p0;
    // 5th degree interpolation
    return (6*t*t*t*t*t-15*t*t*t*t+10*t*t*t)*(p1 - p0) + p0;
}