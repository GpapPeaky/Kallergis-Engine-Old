#include "events.hpp"

auto prev_time = std::chrono::steady_clock::now();
const Uint8* state;

eng_event info_on_hover(void){

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
    /* WRITE */
    return;
}

eng_event events_handling(bool& quit, camera& cam){
    SDL_Event e;
    /* Initial Values For Camera Velocity */
    float vel_x = 1.0f;
    float vel_y = 1.0f;
    state = SDL_GetKeyboardState(NULL); /* Get the state of the keyboard */

    while(SDL_PollEvent(&e)){
        int sw, sh;
        SDL_GetRendererOutputSize(renderer, &sw, &sh); /* For The Camera Readjustment */
        if(e.type == SDL_QUIT){
            quit = true;
        }else if(e.type == SDL_MOUSEWHEEL){
            /* Calculate new zoom level */
            float zoom_factor = (e.wheel.y > 0) ? 1.1f : 0.9f;
            cam.zoom *= zoom_factor;

            if(cam.zoom <= 0.32f) cam.zoom = 0.32f; /* Max zoom out */
            if(cam.zoom >= 15.0f) cam.zoom = 15.0f; /* Max zoom in */

            int center_x = cam.rect.x + cam.rect.w / 2;
            int center_y = cam.rect.y + cam.rect.h / 2;

            int new_w = static_cast<int>(sw / cam.zoom); /* The handle_camera() function had 1000 and 900 px */
            int new_h = static_cast<int>(sh / cam.zoom);

            cam.rect.x = center_x - new_w / 2;
            cam.rect.y = center_y - new_h / 2;
            cam.rect.w = new_w;
            cam.rect.h = new_h;

            /* Out of bounds checks */
            if(cam.rect.x < 0) cam.rect.x = 0;
            if(cam.rect.y < 0) cam.rect.y = 0;
            if(cam.rect.x + cam.rect.w > BMP_WIDTH) cam.rect.x = BMP_WIDTH - cam.rect.w;
            if(cam.rect.y + cam.rect.h > BMP_HEIGHT) cam.rect.y = BMP_HEIGHT - cam.rect.h;
            // std::printf("zoom: %.2f\n", cam.zoom);
        }else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_e){
                // SDL_SaveBMP(map, "bin/output.bmp"); /* FIXME */
                quit = true;
            }
        }else if(e.type == SDL_MOUSEBUTTONDOWN){
            if(e.button.button == SDL_BUTTON_LEFT){
                int mouse_x, mouse_y;
                int unit_x;
                int unit_y;
                SDL_GetMouseState(&mouse_x, &mouse_y); /* We use the untransformed coord for the mouse */

                for(auto& unit : units){
                    /* Transforming unit rect coords */
                    unit_x = static_cast<int>((unit.rect.x - cam.rect.x) * cam.zoom);
                    unit_y = static_cast<int>((unit.rect.y - cam.rect.y) * cam.zoom); /* Reverse transform the coords */

                    // std::printf("Mouse at window coordinates: (%d, %d)\n", mouse_x, mouse_y);
                    // std::printf("Mouse at surface coordinates: (%d, %d)\n", surface_x, surface_y);
                    // std::printf("Checking unit %d with rect: {x: %d, y: %d, w: %d, h: %d}\n", 
                    //             unit.id, unit_x, unit_y, unit.rect.w, unit.rect.h);

                    /* Find the name in the hashtable with the correct id and prov id */
                    // prov* current = provinces_h[h(unit.prov_visited, PROV_M)];
                    // std::string name;

                    // while(current != NULL){
                    //     if(current->prov_id == unit.prov_visited){
                    //         name = current->prov_name;
                    //         break;
                    //     }
                    //     current = current->next;
                    // }

                    if(mouse_x >= unit_x && mouse_x <= unit_x + unit.rect.w &&
                    mouse_y >= unit_y && mouse_y <= unit_y + unit.rect.h){
                        // std::printf("Unit %d at province %d, %s clicked\n__________________________\n", unit.id, unit.prov_visited, name.c_str());
                        selected_unit = &unit;
                        break;
                    }
                    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                        selected_unit = NULL;
                    }
                }

            // highlight_on_click(surface_x, surface_y, click_surface, map); /* FIXME */
            }else if(e.button.button == SDL_BUTTON_RIGHT){
                move_unit(click_surface, cam); /* Move the unit, if able, the check if not NULL is in the function */
            }
        }
    }

    double move_x = 0.0f;
    double move_y = 0.0f;

    /* Unordered map for non-serial movement */
    if(state[SDL_SCANCODE_W]){
        move_y -= 1.0f / cam.zoom;
    }else if(state[SDL_SCANCODE_S]){
        move_y += 1.0f / cam.zoom;
    }else if(state[SDL_SCANCODE_A]){
        move_x -= 1.0f / cam.zoom;
    }else if(state[SDL_SCANCODE_D]){
        move_x += 1.0f / cam.zoom;
    }

    /* WARN: Problematic zoom at 8.0f cam.zoom */

    /* Find the length */
    float length = std::sqrt(move_x * move_x + move_y * move_y);
    if(length > 0.0f){
        move_x /= length;
        move_y /= length;
    }

    /* Apply acceleration to direction */
    vel_x += static_cast<float>((move_x * ACC / cam.zoom) + 0.4f);
    vel_y += static_cast<float>((move_y * ACC / cam.zoom) + 0.4f);

    /* Calculate time elapsed */
    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = current_time - prev_time;
    prev_time = current_time;
    float dt = elapsed.count();

    /* Update the camera x and y */
    cam.rect.x += static_cast<int>(vel_x * dt);
    cam.rect.y += static_cast<int>(vel_y * dt);

    /* Out of bounds checks */
    if(cam.rect.x < 0) cam.rect.x = 0;
    if(cam.rect.y < 0) cam.rect.y = 0;
    if(cam.rect.x + cam.rect.w > BMP_WIDTH) cam.rect.x = BMP_WIDTH - cam.rect.w;
    if(cam.rect.y + cam.rect.h > BMP_HEIGHT) cam.rect.y = BMP_HEIGHT - cam.rect.h;

    /* Decellerate */
    vel_x *= DEC;
    vel_y *= DEC;

    return;
}
