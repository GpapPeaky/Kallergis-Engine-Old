#include <SDL2/SDL.h>

#ifndef CAMERA
/**
 * @brief Camera module for the screen movement
 */
#define CAMERA

typedef struct camera{
    SDL_Rect rect;
    float zoom;
}camera;

/**
 * @brief Camera initialisation 
 * 
 * @param renderer Renderer to base the mid point, out of it's output size
 */
camera init_camera(SDL_Renderer* renderer);

void handle_camera(camera& cam, SDL_Event e);

#endif
