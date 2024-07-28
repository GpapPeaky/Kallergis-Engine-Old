#include "pixels.hpp"
#include "camera.hpp"
#include "map.hpp"

int main(int argv, char* args[]){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError()); return EXIT_FAILURE; }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) { fprintf(stderr, "Unable to initialize IMG: %s\n", SDL_GetError()); return EXIT_FAILURE; }

    SDL_Window* pixel_win = SDL_CreateWindow("C++ Surface And Pixel Manipulation Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 900, SDL_WINDOW_SHOWN); /* Create A Window */
    SDL_Renderer* pixel_renderer = SDL_CreateRenderer(pixel_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */
    if(pixel_win == nullptr){ SDL_Log("Could not create pixels' window: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(pixel_renderer == nullptr){ SDL_Log("Could not create pixels' renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Texture* texture = SDL_CreateTexture(pixel_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    load_bitmap(texture, "history/map/provinces.bmp"); /* Loading an image onto the texture */

    camera cam = init_camera();
    // mark_borders(surface, pixel_win);

    bool quit = false;
    SDL_Event event;
    while(!quit){
        while(SDL_PollEvent(&event)){
            /* Camera movement */
            handle_camera(cam, event);
            
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_e){
                quit = true;
                goto EXIT;
            }
            if(event.key.keysym.sym == SDLK_2){ /* Eyoo! WE CAN EDIT TEXTURES MY NIGGAAASS!!! */
                pixel_screen_fill(texture);
            }
            if(event.key.keysym.sym == SDLK_1){
                for(int i = 0 ; i < 450 ; i++){
                    for(int j = 0 ; j < 300 ; j++){
                        set_pixel(texture, i, j, 255, 0, 0, ALPHA); /* Fill test */
                    }
                }
            }
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState(&x, &y);
                int surface_x = (x / cam.zoom) + cam.rect.x;
                int surface_y = (y / cam.zoom) + cam.rect.y;
                set_pixel(texture, surface_x, surface_y, 255, 255, 255, ALPHA);
            }
            // if(event.key.keysym.sym == SDLK_TAB){
            //     toggle = !toggle;
            //     if(toggle){
            //         colour_box(surface, 0, 0, 200, 200);
            //     }
            // }
            // if(event.button.button == SDL_BUTTON_LEFT){
            //     int x, y;
            //     SDL_GetMouseState(&x, &y);

            //     // int surface_x = (x / cam.zoom) + cam.rect.x;
            //     // int surface_y = (y /cam.zoom) + cam.rect.y;
            //     set_pixel(texture, pixel_win, x, y, 255, 255, 255, ALPHA);
            //     /* Random Colours to be chosen when clicking */
            // }
        }

        SDL_RenderClear(pixel_renderer);
        
        SDL_RenderCopy(pixel_renderer, texture, &cam.rect, NULL);

        SDL_RenderPresent(pixel_renderer);
        /* Fuck me it works... */

        // SDL_UpperBlitScaled(surface, &cam.rect, screen, NULL);
        // SDL_RenderClear(pixel_renderer); /* Canvas clearing  (No need if the window surface is updated)*/
        // SDL_BlitSurface(surface, &cam.rect, screen, NULL); /* Changes the RGB value format, offsets need to be handled differently in the set pixel value */
        // SDL_UpdateWindowSurface(pixel_win); /* Update only when handling the window surface, makes other renditions stutter due to the 
        // RenderClear and RenderPresent functions */   
        // SDL_RenderPresent(pixel_renderer); /* Present copies (No need if the window surface is updated) */
        /* This method is used for the typical SDL_RenderCopy(...) family of functions */
    }

    /* Cleanup */
    EXIT:
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(pixel_renderer);
        SDL_DestroyWindow(pixel_win);
        IMG_Quit();
        SDL_Quit();
        std::printf("Pixel test completed\n");

    return EXIT_SUCCESS;
}
