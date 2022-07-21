/**
 * @file handler.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Set of handlers for a kernel object
 * @version 0.1
 * @date 2022-07-21
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void eventHandler();
void rendererHandler();
void updateHandler();

#endif