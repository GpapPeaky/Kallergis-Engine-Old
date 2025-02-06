#include "KENG_Terrain.hpp"

SDL_Surface* KENG_TerrainSurface;

SDL_Colour KENG_TerrainColours[KENG_TERRAIN_TYPES] = {
    /* RGBA */
    {100, 100, 100, 255},   /* Urban */
    {0, 163, 0, 255},       /* Plains */
    {0, 50, 0, 255},        /* Forest */
    {255, 0, 255, 255},     /* Hills */
    {150, 0, 150, 255},     /* Mountain */
};

SDL_Surface* KENG_TerrainSurfaces[KENG_TERRAIN_TYPES];

void KENG_CreateTerrainSurfaces(void){
    SDL_Surface* urban = SDL_LoadBMP("assets/gfx/terrain/urban.bmp");
    if(!urban){ printf("Failed urban terrain load\n"); return; }

    SDL_Surface* plains = SDL_LoadBMP("assets/gfx/terrain/plains.bmp");
    if(!plains){ printf("Failed plains terrain load\n"); return; }

    SDL_Surface* forest = SDL_LoadBMP("assets/gfx/terrain/forest.bmp");
    if(!forest){ printf("Failed forest terrain load\n"); return; }

    SDL_Surface* hills = SDL_LoadBMP("assets/gfx/terrain/hills.bmp");
    if(!hills){ printf("Failed hills terrain load\n"); return; }
    
    SDL_Surface* mount = SDL_LoadBMP("assets/gfx/terrain/mountain.bmp");
    if(!mount){ printf("Failed mountain terrain load\n"); return; }

    KENG_TerrainSurfaces[KENG_URBAN] = urban;
    KENG_TerrainSurfaces[KENG_PLAIN] = plains;
    KENG_TerrainSurfaces[KENG_FOREST] = forest;
    KENG_TerrainSurfaces[KENG_HILLS] = hills;
    KENG_TerrainSurfaces[KENG_MOUNTAIN] = mount;

    /* Free memory */
    SDL_FreeSurface(urban);
    SDL_FreeSurface(plains);
    SDL_FreeSurface(forest);
    SDL_FreeSurface(hills);
    SDL_FreeSurface(mount);

    /* Load the terrain bmp to a surface */
    KENG_TerrainSurface = SDL_LoadBMP("history/map/terrain/terrain.bmp");
    if(!KENG_TerrainSurface){
        printf("Failed to load terrain surface\n");
        return;
    }

    return;
}

/* FIXME */
SDL_Texture* KENG_ReadTerrainMap(SDL_Surface* terrainMap) {
    if (!terrainMap) {
        printf("Improper terrain surface BMP in terrain read\n");
        return nullptr;
    }

    if (!renderer) {
        printf("Error: SDL renderer is not initialized\n");
        return nullptr;
    }

    SDL_Surface* processedSurface = SDL_CreateRGBSurface(0, terrainMap->w, terrainMap->h, 32,
                                                         0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    if (!processedSurface) {
        printf("Failed to create processed surface: %s\n", SDL_GetError());
        return nullptr;
    }

    SDL_LockSurface(terrainMap);
    SDL_LockSurface(processedSurface);

    Uint32* pixels = (Uint32*)terrainMap->pixels;
    int pitch = terrainMap->pitch / sizeof(Uint32);
    Uint32* dstPixels = (Uint32*)processedSurface->pixels;
    int dstPitch = processedSurface->pitch / sizeof(Uint32);

    for (int y = 0; y < terrainMap->h; y++) {
        for (int x = 0; x < terrainMap->w; x++) {
            Uint32 pixel = pixels[y * pitch + x];

            Uint8 r, g, b;
            SDL_GetRGB(pixel, terrainMap->format, &r, &g, &b);

            if (r == 0 && g == 0 && b == 0) continue;

            for (int i = 0; i < KENG_TERRAIN_TYPES; i++) {
                if (r == KENG_TerrainColours[i].r &&
                    g == KENG_TerrainColours[i].g &&
                    b == KENG_TerrainColours[i].b) {

                    SDL_Surface* tileSurface = KENG_TerrainSurfaces[i];
                    if (!tileSurface) {
                        printf("Error: Terrain surface %d is null\n", i);
                        continue;
                    }

                    SDL_Rect destRect = { x, y, tileSurface->w, tileSurface->h };

                    // If the tile is smaller than the terrain cell, repeat it
                    for (int ty = 0; ty < processedSurface->h; ty += tileSurface->h) {
                        for (int tx = 0; tx < processedSurface->w; tx += tileSurface->w) {
                            SDL_Rect targetRect = { tx, ty, tileSurface->w, tileSurface->h };
                            SDL_BlitSurface(tileSurface, nullptr, processedSurface, &targetRect);
                        }
                    }

                    break;
                }
            }
        }
    }

    SDL_UnlockSurface(terrainMap);
    SDL_UnlockSurface(processedSurface);

    // Convert to texture
    SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer, processedSurface);
    SDL_FreeSurface(processedSurface);

    if (!terrainTexture) {
        printf("Error: Failed to create texture - %s\n", SDL_GetError());
    }

    return terrainTexture;
}
