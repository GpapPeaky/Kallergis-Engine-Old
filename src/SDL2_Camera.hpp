#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_InitWin.hpp"

/**
 * Camera struct
 */
typedef struct SDL2_Camera{
    SDL_Rect cameraRect;            /* Camera view */
    SDL_FPoint offsetFromCamera;    /* Global offset from the camera's 0,0 (top left) */
    float zoom;                     /* Zoom factor */
}SDL2_Camera;

extern SDL2_Camera* SDL2_Cam;

/**
 * @brief Create a new camera
 */
SDL2_Camera* SDL2_NewCamera(void);

/**
 * @brief Free the camera global
 */
void SDL2_FreeCamera(void);

/**
 * @brief Offsets the global offset from the camera
 * 
 * @param dx X change
 * @param dy Y change
 */
void SDL2_MoveCamera(float dx, float dy);

/**
 * @brief Recalibrate the camera zoom
 * 
 * @param factor Multiply zoom by it, smoother transition
 */
void SDL2_RecalibrateZoom(float factor);
