#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../ThirdParty/SDL2/include/SDL2/SDL_image.h"

#include "SDL2_Camera.hpp"                     /* Camera offsets */

/**
 * Bitmap object
 */
typedef struct SDL2_Bitmap{
    SDL_Surface* srfc;          /* Surface object */
    SDL_Texture* txtr;          /* Texture object */
    SDL_FRect pos;              /* Screen coordinates */
}SDL2_Bitmap;

/**
 * @brief Creates a new bitmap
 * 
 * @param fpath File of bitmap to load
 * 
 * @returns The new bitmap
 */
SDL2_Bitmap* SDL2_NewBitmap(const char* fpath);

/**
 * @brief Recalibarte the bitmap texture, if the surface has changed
 * 
 * @param bp Bitmap to recalibrate the surface of
 */
void SDL2_RecalibrateBitmapTexture(SDL2_Bitmap* bp);

/**
 * @brief Recalibrate the bitmap texture size
 * by modifying the pos rectangle (aspect ratio locked)
 * 
 * @param bp Bitmap to change the size of 
 * @param size New size
 */
void SDL2_RecalibrateBitmapSizeAspectRatioLocked(SDL2_Bitmap* bp, float size);

/**
 * @brief Recalibrate the bitmap texture size
 * by modifying the pos rectangle (aspect ratio ignored)
 * 
 * @param bp Bitmap to change the size of 
 * @param w New width
 * @param h New height
 */
void SDL2_RecalibrateBitmapSize(SDL2_Bitmap* bp, float w, float h);

/**
 * @brief Deallocates memory used by the bitmap
 * 
 * @param bp Bitmap to free
 */
void SDL2_FreeBitmap(SDL2_Bitmap* bp);

/**
 * @brief Render a bitmap in its specified positions
 * 
 * @param bp Bitmap to render
 * @param srcRect Source rectangle to read from the bp texture
 */
void SDL2_RenderBitmap(SDL2_Bitmap* bp, SDL_Rect* srcRect = nullptr);
