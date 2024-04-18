#include "includes.aux"

int main(int argv, char* args[]){

    win_init("win");
    prov_to_reg("src/regions/regions.mdf"); /* Relative to the executable location */   
    reg_names("src/regions/region_names.ndf");
    scan_png_map("src/regions/region.png");

    print_regions();

    while(1){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_Rect rect = { 0, 0, map_surface->w, map_surface->h };
        SDL_RenderCopy(renderer, map_texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }

    std::printf("terminates correctly\n");

    return EXIT_SUCCESS;
}
