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

#include "kernel/kernel.h"
#include "handlers/handler.h"

int main(int argc, char* argv[]) {
    Kernel* kernel = new Kernel(string("Hola Terra!"), 500, 500);
    
    
    delete kernel;

    return 0;
}