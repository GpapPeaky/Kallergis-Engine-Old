#include "events.hpp"

auto prev_time = std::chrono::steady_clock::now();
const Uint8* state;

eng_event info_on_hover(void){

    /* WRITE */
    /* Info box: 129 - 114 */
    return;
}

eng_event highlight_on_click(int x, int y, SDL_Surface* src, SDL_Texture* dst){
    Uint8 r, g, b;

    /* Bounds check */
    if(x < 0 || x >= src->w || y < 0 || y >= src->h){
        return;
    }

    int src_bpp = src->format->BytesPerPixel;
    int index = y * src->pitch + x * src_bpp; /* bpp usually 3 or 4 */
    Uint8* pixels = (Uint8*)src->pixels;

    b = ((Uint8*)pixels)[index + 0];
    g = ((Uint8*)pixels)[index + 1];
    r = ((Uint8*)pixels)[index + 2];

    SDL_Color clicked = { r, g, b, ALPHA };
    int id;

    for(int i = 0 ; i < prov_hash_s ; i++){
        prov* current = provinces_h[h(i, PROV_M)];
        while(current != NULL){
            if(current->prov_colour.r == clicked.r && current->prov_colour.g == clicked.g && current->prov_colour.b == clicked.b){
                std::printf("Clicked Province: %s - <%d, %d, %d>\n", current->prov_name.c_str(), current->prov_colour.r, current->prov_colour.g, current->prov_colour.b);
                id = current->prov_id;
                return;
            }
            current = current->next;
        }
    }

    return;
}

eng_event pan_map(int d_x, int d_y){
    return;
}

void events_handling(bool& quit, camera& cam){
    SDL_Event e;
    /* Initial Values For Camera Velocity */
    float vel_x = 1.0f;
    float vel_y = 1.0f;
    state = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&e)){
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h); /* For The Camera Readjustment */
        if(e.type == SDL_QUIT){
            quit = true;
        }else if(e.type == SDL_MOUSEWHEEL){
            /* Calculate new zoom level */
            /* FIXME: it bugs if we zoom in or out too much */ 
            float zoom_factor = (e.wheel.y > 0) ? 1.1f : 0.9f;
            cam.zoom *= zoom_factor;

            if(cam.zoom < 0.1f) cam.zoom = 0.1f;
            if(cam.zoom > 10.0f) cam.zoom = 10.0f;

            int center_x = cam.rect.x + cam.rect.w / 2;
            int center_y = cam.rect.y + cam.rect.h / 2;

            int new_w = static_cast<int>(w / cam.zoom); /* The handle_camera() function had 1000 and 900 px */
            int new_h = static_cast<int>(h / cam.zoom);

            cam.rect.x = center_x - new_w / 2;
            cam.rect.y = center_y - new_h / 2;
            cam.rect.w = new_w;
            cam.rect.h = new_h;
        }else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_e){
                // SDL_SaveBMP(map, "bin/output.bmp"); /* FIXME */
                quit = true;
            }
        }else if(e.type == SDL_MOUSEBUTTONDOWN){
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            int surface_x = (mouse_x / cam.zoom) + cam.rect.x;
            int surface_y = (mouse_y / cam.zoom) + cam.rect.y;
            // highlight_on_click(surface_x, surface_y, click_surface, map); /* FIXME */
        }
    }

    float move_x = 0.0f;
    float move_y = 0.0f;

    /* Unordered map for non-serial movement */
    if(state[SDL_SCANCODE_W]){
        move_y -= 1.0f;
    }else if(state[SDL_SCANCODE_S]){
        move_y += 1.0f;
    }else if(state[SDL_SCANCODE_A]){
        move_x -= 1.0f;
    }else if(state[SDL_SCANCODE_D]){
        move_x += 1.0f;
    }

    /* Find the length */
    float length = std::sqrt(move_x * move_x + move_y * move_y);
    if(length > 0.0f){
        move_x /= length;
        move_y /= length;
    }

    /* Apply acceleration to direction */
    vel_x += move_x * ACC / cam.zoom;
    vel_y += move_y * ACC / cam.zoom;

    /* Find the camera speed and cap it if it exceeds the max camera speed macro */
    float speed = std::sqrt(vel_x * vel_x + vel_y * vel_y);
    if(speed > MAX_CAMERA_SPEED){
        vel_x = (vel_x / speed) * MAX_CAMERA_SPEED;
        vel_y = (vel_y / speed) * MAX_CAMERA_SPEED;
    }

    /* Calculate time elapsed */
    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = current_time - prev_time;
    prev_time = current_time;
    float dt = elapsed.count();

    /* Update the camera x and y */
    cam.rect.x += static_cast<int>(vel_x * dt);
    cam.rect.y += static_cast<int>(vel_y * dt);

    /* Decellerate */
    vel_x *= DEC;
    vel_y *= DEC;

    return;
}
