#include "SDL2_Events.hpp"

auto prev_time = std::chrono::steady_clock::now();
const Uint8* state;
prov* clicked_province;

prov* SDL2_HighlightOnClick(int x, int y, SDL_Surface* src, SDL_Texture* dst, camera cam){
    int world_x = static_cast<int>(x / cam.zoom + cam.rect.x);
    int world_y = static_cast<int>(y / cam.zoom + cam.rect.y);

    /* TODO: Make it so that when a unit is clicked, no province print is shown */
    
    int src_bpp = src->format->BytesPerPixel;
    Uint8* pixels = (Uint8*)src->pixels;

    /* Pixel at mouse position */
    Uint32 pixel = 0;
    Uint8* pixel_ptr = pixels + (world_y * src->pitch) + (world_x * src_bpp);

    SDL_LockSurface(src);

    switch(src_bpp){
        case 3: /* 24-bit format (little-endian) */
            pixel = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
            break;
        case 4: /* 32-bit format */
            pixel = *(Uint32*)pixel_ptr;
            break;
        default:
            std::printf("Unsupported pixel format\n");
            SDL_UnlockSurface(src);
            return NULL;
    }
    Uint8 r, g, b;
    SDL_GetRGB(pixel, src->format, &r, &g, &b);

    SDL_Color clicked = { r, g, b, ALPHA };
    int id;

    for(auto prov : provinces){
        if(prov->prov_colour.r == clicked.b && prov->prov_colour.g == clicked.g && prov->prov_colour.b == clicked.r){ /* HUH? Little Endian ??? */

        #ifdef PRINT_CLICK
            std::printf("Clicked Province: %s - <%d, %d, %d>  Dev: <%d %d %d> Infr: %d Goods: %s Pops: %d\n", prov->prov_name.c_str(), prov->prov_colour.r, prov->prov_colour.g, prov->prov_colour.b, 
            prov->province_economy.development.admin, prov->province_economy.development.mil, prov->province_economy.development.prod,
            prov->province_economy.infrastructure, goods_names[prov->province_economy.local_goods.good], prov->province_economy.local_goods.population);
        #endif

            id = prov->prov_id;
            return prov; /* Return a pointer to the clicked province update the arguments for the province box */
        }
    }

    return NULL;
}

void SDL2_PanScreen(int d_x, int d_y){
    /* WRITE */
    return;
}

void SDL2_HandleEvents(bool& quit, camera& cam){
    SDL_Event e;
    /* Initial Values For Camera Velocity */
    float vel_x = 1.0f;
    float vel_y = 1.0f;
    state = SDL_GetKeyboardState(NULL); /* Get the state of the keyboard */

    while(SDL_PollEvent(&e)){
        int sw, sh; /* Rendering output width and height */
        SDL_GetRendererOutputSize(renderer, &sw, &sh); /* For The Camera Readjustment */
        if(e.type == SDL_QUIT){
            quit = true;
        }else if(e.key.keysym.sym == SDLK_SPACE){
            KENG_gamePause = !(KENG_gamePause); /* Switching the, pausing */
        }else if(e.key.keysym.sym == SDLK_1){
            KENG_gameSpeed = SPEED1_CYCLES_PER_UPDATE;
        }else if(e.key.keysym.sym == SDLK_2){
            KENG_gameSpeed = SPEED2_CYCLES_PER_UPDATE;
        }else if(e.key.keysym.sym == SDLK_3){
            KENG_gameSpeed = SPEED3_CYCLES_PER_UPDATE;
        }else if(e.key.keysym.sym == SDLK_4){
            KENG_gameSpeed = SPEED4_CYCLES_PER_UPDATE;
        }else if(e.key.keysym.sym == SDLK_5){
            KENG_gameSpeed = SPEED5_CYCLES_PER_UPDATE;
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
                    // prov* prov = provinces_h[h(unit.prov_visited, PROV_M)];
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

                if(KENG_MouseIntersectingWithProvinceGUICheck(mouse_x, mouse_y, KENG_clickSurface, cam) == true){ 
                    PGUI_EventCycle(mouse_x, mouse_y); /* Execute the button action */
                }else{
                    clicked_province = SDL2_HighlightOnClick(mouse_x, mouse_y, KENG_clickSurface, map, cam); /* Click a new province */
                }
            }else if(e.button.button == SDL_BUTTON_RIGHT){
                KENG_MoveUnit(KENG_clickSurface, cam); /* Move the unit, if able, the check if not NULL is in the function */
            }
        }
    }

    double move_x = 0.0f;
    double move_y = 0.0f;

    /* Unordered map for non-serial movement */
    if(state[SDL_SCANCODE_W]){
        move_y -= CAMERA_MOVE_SPEED;
    }else if(state[SDL_SCANCODE_S]){
        move_y += CAMERA_MOVE_SPEED;
    }else if(state[SDL_SCANCODE_A]){
        move_x -= CAMERA_MOVE_SPEED;
    }else if(state[SDL_SCANCODE_D]){
        move_x += CAMERA_MOVE_SPEED;
    }

    /* WARN: Problematic zoom at 8.0f cam.zoom */

    /* Find the length */
    float length = std::sqrt(move_x * move_x + move_y * move_y);
    if(length > 0.0f){
        move_x /= length;
        move_y /= length;
    }

    /* Apply acceleration to direction */
    vel_x += static_cast<float>((move_x * ACC) + 0.01f);
    vel_y += static_cast<float>((move_y * ACC) + 0.01f);

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

bool KENG_MouseIntersectingWithProvinceGUICheck(int mx, int my, SDL_Surface* KENG_clickSurface, camera cam){
    /* Transform the mouse coords */
    int world_x = static_cast<int>(mx / cam.zoom + cam.rect.x);
    int world_y = static_cast<int>(my / cam.zoom + cam.rect.y);

    bool insidePGUIItemRect = false;

    /* Check if the mouse is inside a UI component */
    for(const auto& item : PGUI_GlobalItems){
        SDL_Rect rect = item.second->itemComponent.rect;

        if(mx >= rect.x && mx <= rect.x + rect.w &&
            my >= rect.y && my <= rect.y + rect.h){
            insidePGUIItemRect = true;
            break;
        }
    }

    /* Check if the mouse is inside a province */
    int src_bpp = KENG_clickSurface->format->BytesPerPixel;
    Uint8* pixels = (Uint8*)KENG_clickSurface->pixels;
    Uint8* pixel_ptr = pixels + (world_y * KENG_clickSurface->pitch) + (world_x * src_bpp);

    SDL_LockSurface(KENG_clickSurface);

    Uint32 pixel = 0;
    switch(src_bpp){
        case 3: /* 24-bit format (little-endian) */
            pixel = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
            break;
        case 4: /* 32-bit format */
            pixel = *(Uint32*)pixel_ptr;
            break;
        default:
            std::printf("Unsupported pixel format\n");
            SDL_UnlockSurface(KENG_clickSurface);
            return false;
    }

    SDL_UnlockSurface(KENG_clickSurface);

    return (insidePGUIItemRect == true); /* Return the intersection */
}
