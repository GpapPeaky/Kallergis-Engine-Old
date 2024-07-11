#include "cleanup.hpp"

void cleanup(SDL_Window* win, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    std::printf("terminates correctly\n"); /* Exit Callback */

    return;
}
