#include "pixels.h"

int main(int argv, char* args[]){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError()); return EXIT_FAILURE; }
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* pixel_win = SDL_CreateWindow("C++ Surface And Pixel Manipulation Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 900, SDL_WINDOW_SHOWN); /* Create A Window */
    SDL_Renderer* pixel_renderer = SDL_CreateRenderer(pixel_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */

    if(pixel_win == nullptr){
        SDL_Log("Could not create pixels' window: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(pixel_renderer == nullptr){
        SDL_Log("Could not create pixels' renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    std::printf("Pixel Intialisation Complete!\n");

    SDL_Surface* surface = SDL_GetWindowSurface(pixel_win);

    bool quit = false;
    SDL_Event event;

    while(!quit){
        while(SDL_PollEvent(&event)){
            srand(time(NULL)); /* Change seed with every loop */
            
            int x, y;
            SDL_GetMouseState(&x, &y); /* Take the mouse state every time */

            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_e){
                quit = true;
                goto EXIT;
            }
            if(event.key.keysym.sym == SDLK_1){
                pixel_screen_fill(surface); /* Makes the colour white */
            }
            if(event.key.keysym.sym == SDLK_2){
                for(int i = 0 ; i < 450 ; i++){
                    for(int j = 0 ; j < 300 ; j++){
                        set_pixel(surface, pixel_win, j, i, 255, 0, 0); /* Fill test */
                    }
                }
            }
            if(event.button.button == SDL_BUTTON_LEFT){
                set_pixel(surface, pixel_win, x, y, rand() % 255, rand() % 255, rand() % 255);
                /* Random Colours to be chosen when clicking */
            }
        }

        SDL_RenderClear(pixel_renderer); /* Canvas clearing */

        SDL_UpdateWindowSurface(pixel_win); /* Update */

        SDL_RenderPresent(pixel_renderer); /* Present copies */
    }

    /* Cleanup */
    EXIT:
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(pixel_renderer);
        SDL_DestroyWindow(pixel_win);
        SDL_Quit();
        std::printf("Pixel test completed\n");

    return EXIT_SUCCESS;
}
