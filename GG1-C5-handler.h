/**
 * @file GG1-C5-handler.h
 * @author Eron Ristich (eron@ristich.com)
 * @brief Handler class for GG1-C5, 
 * @version 0.1
 * @date 2022-07-22
 */

#ifndef GG1_C5_HANDLER_H
#define GG1_C5_HANDLER_H

#include "util/handler.h"
#include "objects/helper.h"
#include "objects/camera.h"

class GG1_C5_Handler : public Handler {
    public:
        GG1_C5_Handler();
        ~GG1_C5_Handler();

        void objEventHandler() override;
        void objRendererHandler() override;
        void objUpdateHandler() override;

    private:
        int relX, relY;
        bool wDown, aDown, sDown, dDown, spDown, shDown, enDown;
        Camera* camera;
};

#endif


