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

    SDL_Surface* screen = SDL_GetWindowSurface(pixel_win);
    SDL_Surface* surface = IMG_Load("history/map/provinces.bmp");
    if(!surface){
        std::printf("Image Failed to Load\n");
    }

    int w, h;
    SDL_GetRendererOutputSize(pixel_renderer, &w, &h); /* Due to the windows high dpi and other parameters, we cannot use SDL_GetWindowSize etc */
    std::printf("WIDTH: %d - HEIGHT: %d\n", w, h);
    surface = resize_bitmap(surface, 5760, 3240); /* Retain the actual size of the bitmap, to not lose quality */

    camera cam = init_camera();
    // mark_borders(surface, pixel_win);

    bool quit = false;
    SDL_Event event;
    while(!quit){
        srand(time(NULL)); /* Change seed with every loop */
        while(SDL_PollEvent(&event)){
            /* Camera movement */
            handle_camera(cam, event);
            
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_e){
                quit = true;
                goto EXIT;
            }
            if(event.key.keysym.sym == SDLK_1){ /* Eyoo! */
                pixel_screen_fill(surface, pixel_win);
            }
            if(event.key.keysym.sym == SDLK_2){
                for(int i = 0 ; i < 450 ; i++){
                    for(int j = 0 ; j < 300 ; j++){
                        set_pixel(surface, pixel_win, j, i, 255, 0, 0); /* Fill test */
                    }
                }
            }
            // if(event.key.keysym.sym == SDLK_TAB){
            //     toggle = !toggle;
            //     if(toggle){
            //         colour_box(surface, 0, 0, 200, 200);
            //     }
            // }
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState(&x, &y);

                int surface_x = (x / cam.zoom) + cam.rect.x;
                int surface_y = (y /cam.zoom) + cam.rect.y;
                set_pixel(surface, pixel_win, surface_x, surface_y, 255, 255, 255);
                /* Random Colours to be chosen when clicking */
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        
        // Blit the surface with camera rect handling
        SDL_UpperBlitScaled(surface, &cam.rect, screen, NULL);

        // Update the window surface
        SDL_UpdateWindowSurface(pixel_win);

        // SDL_RenderClear(pixel_renderer); /* Canvas clearing  (No need if the window surface is updated)*/
        // SDL_RenderCopy(pixel_renderer, texture, NULL, NULL);
        // SDL_BlitSurface(surface, &cam.rect, screen, NULL); /* Changes the RGB value format, offsets need to be handled differently in the set pixel value */
        // SDL_UpdateWindowSurface(pixel_win); /* Update only when handling the window surface, makes other renditions stutter due to the 
        // RenderClear and RenderPresent functions */   
        // SDL_RenderPresent(pixel_renderer); /* Present copies (No need if the window surface is updated) */
        /* This method is used for the typical SDL_RenderCopy(...) family of functions */
    }

    /* Cleanup */
    EXIT:
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(pixel_renderer);
        SDL_DestroyWindow(pixel_win);
        IMG_Quit();
        SDL_Quit();
        std::printf("Pixel test completed\n");

    return EXIT_SUCCESS;
}
