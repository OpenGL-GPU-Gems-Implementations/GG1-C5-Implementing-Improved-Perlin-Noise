/**
 * @file GG1-C5-handler.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Handler class for GG1-C5, 
 * @version 0.1
 * @date 2022-07-22
 */

#ifndef GG1_C5_HANDLER_H
#define GG1_C5_HANDLER_H

#include <chrono>

#include "util/handler.h"
#include "objects/helper.h"
#include "objects/camera.h"
#include "GG1-C5/src/perlin/superquadric.h"

class GG1_C5_Handler : public Handler {
    public:
        GG1_C5_Handler();
        ~GG1_C5_Handler();

        void objEventHandler() override;
        void objRendererHandler() override;
        void objUpdateHandler() override;
        void objPreLoopStep() override;

    private:
        int frame = 0;
        float dt = 0.0f;
        int curFPS = 0;
        std::chrono::_V2::steady_clock::time_point lastT;

        int relX, relY;
        bool wDown, aDown, sDown, dDown, spDown, shDown, enDown;
        Camera* camera;

        // scene objects
        /* ----- CUBE ----- */
        unsigned int cubeVBO, cubeVAO;
        Shader* cubeShader;

        /* ----- MINI MESH ----- */
        MiniMesh* miniMesh;
        Superquadric* superquadric;
        
};

#endif


