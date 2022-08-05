/**
 * @file main.cpp
 * @author Eron Ristich (eron@ristich.com)
 * @brief Open SDL window
 * @version 0.1
 * @date 2022-07-20
 */

#include <iostream>
#include <string>
using std::cout;
using std::string;

#include "util/kernel/kernel.h"
#include "util/handler.h"
#include "GG1-C5-handler.h"
#include "GG1-C5/src/perlin/cspline/cspline.h"
#include "GG1-C5/src/perlin/superquadric.h"

int main(int argc, char* argv[]) {
    Kernel* kernel = new Kernel(string("GG1-C5"), 500, 500);
    GG1_C5_Handler* handler = new GG1_C5_Handler();

    GG1_C5_Handler::registerKernel(kernel);
    GG1_C5_Handler::registerHandler(handler);

    kernel->start();
    
    delete kernel;

    return 0;
}