#include "SDL2_CleanUp.hpp"

void SDL2_Cleanup(SDL_Window* win, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    std::printf("Main Exitted Correctly\n"); /* Exit Callback */

    return;
}
