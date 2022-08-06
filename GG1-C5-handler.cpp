/**
 * @file GG1-C5-handler.cpp
 * @author Eron Ristich (eron@ristich.com)
 * @brief Handler class for GG1-C5, 
 * @version 0.1
 * @date 2022-07-22
 */

#include "GG1-C5-handler.h"

GG1_C5_Handler::GG1_C5_Handler() {
    wDown = false; aDown = false; sDown = false; dDown = false; spDown = false; shDown = false; enDown = false;
    camera = new Camera(glm::vec3(2.8963, 0.35203, -1.65028), glm::vec3(0, 1, 0), -209.7, -6.2);
    camera->movementSpeed = 20.0f;
}

GG1_C5_Handler::~GG1_C5_Handler() {
    delete camera;
}

void GG1_C5_Handler::objEventHandler() {
    relX = 0; relY = 0;
    SDL_Event m_event;
	while(SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
            case SDL_KEYDOWN:
                switch (m_event.key.keysym.sym) {
                    case SDLK_ESCAPE: // exit window
                        kernel->stop();
                        break;
                    case SDLK_w: // w
                        wDown = true;
                        break;
                    case SDLK_a: // a
                        aDown = true;
                        break;
                    case SDLK_s: // s
                        sDown = true;
                        break;
                    case SDLK_d: // d
                        dDown = true;
                        break;
                    case SDLK_SPACE: // spacebar
                        spDown = true;
                        break;
                    case SDLK_LSHIFT: // left shift
                        shDown = true;
                        break;
                    case SDLK_RETURN: // enter
                        enDown = true;
                        std::cout << "Camera position: " << camera->position.x << " " << camera->position.y << " " << camera->position.z << endl;
                        std::cout << "Camera orientation: " << camera->yaw << " " << camera->pitch << endl;
                        break;
                }
                break;
            
            case SDL_KEYUP:
                switch (m_event.key.keysym.sym) {
                    case SDLK_w: // w
                        wDown = false;
                        break;
                    case SDLK_a: // a
                        aDown = false;
                        break;
                    case SDLK_s: // s
                        sDown = false;
                        break;
                    case SDLK_d: // d
                        dDown = false;
                        break;
                    case SDLK_SPACE: // spacebar
                        spDown = false;
                        break;
                    case SDLK_LSHIFT: // left shift
                        shDown = false;
                        break;
                    case SDLK_RETURN: // enter
                        enDown = false;
                        break;
                }
                break;

            case SDL_WINDOWEVENT:
                switch (m_event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE: // exit window
                        kernel->stop();
                        break;
                }
                break;
            
            case SDL_MOUSEMOTION:
                relX = m_event.motion.xrel;
                relY = m_event.motion.yrel;
                break;
        }
	}
}

void GG1_C5_Handler::objRendererHandler() {
    glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)kernel->getRX() / (float)kernel->getRY(), 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();
    
    // perlin cube
    cubeShader->use();
    cubeShader->setInt("iFrame", frame);
    cubeShader->setVec3("objColor", 1.0f, 0.3137f, 0.5569f);//0.31f, 0.5f, 1.0f);//0.5f, 0.31f, 1.0f);
    cubeShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    cubeShader->setVec3("lightPos", -2.0f, -2.0f, -2.0f);
    cubeShader->setVec3("viewPos", camera->position);
    cubeShader->setMat4("projection", projection);
    cubeShader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    cubeShader->setMat4("model", model);

    /*
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    */

    // mini mesh
    //miniMesh->draw();
    superquadric->draw();
}

void GG1_C5_Handler::objUpdateHandler() {
    // update time
    frame ++;
    auto curT = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = curT - lastT;
    lastT = std::chrono::steady_clock::now();
    dt = diff.count();
    curFPS = (int)(1/dt);

    // update title
    string atitle = kernel->getTitle() + string(" - FPS: ") + std::to_string(curFPS) + string(" - Frame: ") + std::to_string(frame);
    SDL_SetWindowTitle(kernel->getWindow(), atitle.c_str());

    // update camera
    int end = NONE;
    if (wDown)
        end |= FORWARD;
    if (aDown)
        end |= LEFT;
    if (sDown)
        end |= BACKWARD;
    if (dDown)
        end |= RIGHT;
    if (spDown)
        end |= UP;
    if (shDown)
        end |= DOWN;
    camera->updateKeyboard(end, dt);
    camera->updateMouse(relX, -relY);
}

void GG1_C5_Handler::objPreLoopStep() {
    lastT = std::chrono::steady_clock::now();
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    cubeShader = new Shader("GG1-C5/src/gl/perlin/cube.vs", "GG1-C5/src/gl/perlin/cube.fs");

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // mini mesh
    //miniMesh = genCube(20, 20, 20);
    superquadric = new Superquadric(7, 2);
}