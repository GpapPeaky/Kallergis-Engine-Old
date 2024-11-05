#include "SDL2_Camera.hpp"

camera SDL2_CreateCamera(void){
    SDL_Rect rect = { 0, 0, BMP_WIDTH, BMP_HEIGHT };

    camera cam = { rect, 1.0f };

    return cam;
}

void SDL2_HandleCamera(camera& cam, SDL_Event e) {
    // Check for mouse wheel events
    if (e.type == SDL_MOUSEWHEEL) {
        // Calculate new zoom level
        float new_zoom = cam.zoom;
        if (e.wheel.y > 0) {
            // Scroll up, zoom in
            new_zoom *= 1.1f;
        } else if (e.wheel.y < 0) {
            // Scroll down, zoom out
            new_zoom *= 0.9f;
        }

        // Ensure the new zoom level stays within reasonable bounds
        if (new_zoom < 0.1f) new_zoom = 0.1f;
        if (new_zoom > 10.0f) new_zoom = 10.0f;

        // Calculate the center of the current view
        int center_x = cam.rect.x + cam.rect.w / 2;
        int center_y = cam.rect.y + cam.rect.h / 2;

        // Calculate new camera rect based on the new zoom level
        int new_w = static_cast<int>(1000 / new_zoom);
        int new_h = static_cast<int>(900 / new_zoom);

        // Center the camera rect around the previous center
        cam.rect.x = center_x - new_w / 2;
        cam.rect.y = center_y - new_h / 2;
        cam.rect.w = new_w;
        cam.rect.h = new_h;

        // Update the zoom level
        cam.zoom = new_zoom;
    }
    // Check for keyboard events
    else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                cam.rect.y -= 150 / cam.zoom;
                break;
            case SDLK_s:
                cam.rect.y += 150 / cam.zoom;
                break;
            case SDLK_a:
                cam.rect.x -= 150 / cam.zoom;
                break;
            case SDLK_d:
                cam.rect.x += 150 / cam.zoom;
                break;
        }
    }
}
