#include "SDL2_Camera.hpp"

SDL2_Camera* SDL2_Cam;

SDL2_Camera* SDL2_NewCamera(void){
    SDL2_Camera* newCam = new SDL2_Camera();
    newCam->cameraRect = { 0, 0, SDL2_WinWidth, SDL2_WinHeight };
    newCam->offsetFromCamera = { 0.0F, 0.0F };
    newCam->zoom = 1.0f;

    return newCam;
}

void SDL2_FreeCamera(void){
    delete SDL2_Cam;

    return;
}

void SDL2_MoveCamera(float dx, float dy){
    SDL2_Cam->offsetFromCamera.x -= dx;
    SDL2_Cam->offsetFromCamera.y -= dy;

    return;
}

void SDL2_RecalibrateZoom(float factor){
    SDL2_Cam->zoom *= factor;

    if(SDL2_Cam->zoom < 0.1f) SDL2_Cam->zoom = 0.1f;   /* Max zoom-in */
    if(SDL2_Cam->zoom > 10.0f) SDL2_Cam->zoom = 10.0f; /* Max zoom-out */

    return;
}
