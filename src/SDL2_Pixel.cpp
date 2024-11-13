#include "SDL2_Pixel.hpp"

int SDL2_SetPixel(SDL_Texture* texture, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255){
    void* pixels = NULL;
    int pitch = 0;
    int bpp; /* Calculate bytes per pixel */
    Uint8* pixel_array; /* Array of the image's pixels */
    Uint8* p; /* Specified pixel */
    Uint32 format; /* To allocate memory for the SDL_PixelFormat* */
    Uint32 pixel_value; /* Value of the pixel based on the rgba, for editing opacity in images with bpp => 4 */

    if(SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) < 0){
        std::printf("Problematic texture\n");
        return FAIL;
    } /* Lock in order to edit */

    SDL_QueryTexture(texture, &format, NULL, NULL, NULL); /* Query the format of the texture */
    SDL_PixelFormat* pixel_format = SDL_AllocFormat(format);/* Get the pixel format */
    if(!pixel_format){
        std::printf("Bad pixel format\n");
        SDL_FreeFormat(pixel_format);
        SDL_UnlockTexture(texture);
        return FAIL;
    }

    /* Calculate the pixel position in the pixels array */
    bpp = pixel_format->BytesPerPixel; /* Find the bytes per pixel of the texture, from it's format */
    pixel_array = static_cast<Uint8*>(pixels);
    p = pixel_array + y * pitch + x * bpp; /* Pixel to change */

    switch(bpp){
        case 3: /* 24 bit surface */
            p[0] = r;
            p[1] = g;
            p[2] = b;
            break;
        case 4:
            pixel_value = SDL_MapRGBA(pixel_format, r, g, b, a);
            *reinterpret_cast<Uint32*>(p) = pixel_value;
            break;
        default:
            SDL_FreeFormat(pixel_format);
            SDL_UnlockTexture(texture);
            std::printf("Unsupported pixel format\n");
            break;
    }
    SDL_UnlockTexture(texture); /* Unlock the texture */
    SDL_FreeFormat(pixel_format); /* Deallocate the format */

    return SUCCESS;
}

void SDL2_PixelScreenFill(SDL_Texture* texture){
    void* pixels = NULL;
    int w, h; /* Width and height*/
    int pitch = 0;
    int bpp; /* Calculate bytes per pixel */
    Uint8* p; /* Specified pixel */
    Uint8* pixel_array; /* Array of the image's pixels */
    Uint32 format; /* To allocate memory for the SDL_PixelFormat* */

    if(SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) < 0){
        std::printf("Problematic texture\n");
        exit(EXIT_FAILURE);
    } /* Lock in order to get the data required */
    SDL_UnlockTexture(texture); /* We unlock since the SDL2_SetPixel function locks and unlocks the texture, ( No locked texture can be locked again if not unlocked )*/

    SDL_QueryTexture(texture, &format, NULL, &w, &h); /* Query the format of the texture */
    SDL_PixelFormat* pixel_format = SDL_AllocFormat(format);/* Get the pixel format */
    if(!pixel_format){
        std::printf("Bad pixel format\n");
        SDL_FreeFormat(pixel_format);
        SDL_UnlockTexture(texture);
        return;
    }

    /* Calculate the pixel position in the pixels array */
    bpp = pixel_format->BytesPerPixel; /* Find the bytes per pixel of the texture, from it's format */
    pixel_array = static_cast<Uint8*>(pixels);

    for(int i = 0 ; i < w ; i++){
        for(int j = 0 ; j < h ; j++){
            p = pixel_array + j * pitch + i * bpp; /* Pixel to change */
            if(
                p[0] == 0 &&
                p[1] == 0 &&
                p[2] == 0
            ){
                SDL2_SetPixel(texture, i, j, 255, 255, 255, ALPHA); /* Simple Example of image manipulation, quite fast... */
            }
        }
    }
    SDL_FreeFormat(pixel_format);

    return;
}

int SDL2_LoadBitmap(SDL_Texture* dest, const char* filename){
    SDL_Surface* src = SDL_LoadBMP(filename);
    if(!src){
        std::printf("Loading bitmap failed, path not found: %s\n", filename);
        return FAIL;
    }

    Uint8* pixels = (Uint8*)src->pixels;
    int w = src->w;
    int h = src->h;
    int sh, sw;
    SDL_QueryTexture(dest, NULL, NULL, &sw, &sh);
    if(sw != w || sh != h){
        std::printf("Incompatible sizes between the bitmap and the texture | bitmap: %d x %d | texture: %d x %d\n", w, h, sw, sh);
        return FAIL;
    }

    for(int j = 0 ; j < h ; j++){
        for(int i = 0 ; i < w ; i++){
            Uint8* p = pixels + j * src->pitch + i * src->format->BytesPerPixel;
            Uint8 r = p[0];
            Uint8 g = p[1];
            Uint8 b = p[2];
            SDL2_SetPixel(dest, i, j, b, g, r, ALPHA); /* HUH?: Little endian ??? */
        }
    }

    SDL_FreeSurface(src);
    return SUCCESS;
}

int SDL2_LoadPNG(SDL_Texture* dest, const char* filename){
    SDL_Surface* src = IMG_Load(filename);
    if(!src){
        std::printf("Loading png failed, path not found: %s\n", filename);
        return FAIL;
    }

    Uint8* pixels = (Uint8*)src->pixels;
    int w = src->w;
    int h = src->h;
    int sh, sw;
    SDL_QueryTexture(dest, NULL, NULL, &sw, &sh);
    if(sw != w || sh != h){
        std::printf("Incompatible sizes between the bitmap and the texture | bitmap: %d x %d | texture: %d x %d\n", w, h, sw, sh);
        return FAIL;
    }

    for(int j = 0 ; j < h ; j++){
        for(int i = 0 ; i < w ; i++){
            Uint8* p = pixels + j * src->pitch + i * src->format->BytesPerPixel;
            Uint8 r = p[0];
            Uint8 g = p[1];
            Uint8 b = p[2];
            Uint8 a = (src->format->BytesPerPixel == 4) ? p[3] : 255;
            SDL2_SetPixel(dest, i, j, b, g, r, a); /* HUH?: Little endian ??? */
        }
    }

    SDL_FreeSurface(src);

    return SUCCESS;
}

int KENG_MarkCountries(SDL_Surface* src, SDL_Texture* texture){
    /* We need to check for Non-black pixels */
    if(!src){
        std::printf("Loading bitmap failed, path not found\n");
        return FAIL;
    }
    int bpp = src->format->BytesPerPixel;
    int pitch = src->pitch;
    Uint8* pixel_array = (Uint8*)src->pixels;
    for(int i = 0 ; i < src->w ; i++){
        for(int j = 0 ; j < src->h ; j++){
            if(
                pixel_array[j * pitch + i * bpp + 0] != 0 &&
                pixel_array[j * pitch + i * bpp + 1] != 0 &&
                pixel_array[j * pitch + i * bpp + 2] != 0
            ){
                /* Save the pixel for more checks */
                Uint8 r, g, b;
                r = pixel_array[j * pitch + i * bpp + 2]; /* Little endian */
                g = pixel_array[j * pitch + i * bpp + 1];
                b = pixel_array[j * pitch + i * bpp + 0];
                /* It doesn't check for countries? */
                for(auto& cou : KENG_globalCountries){
                    SDL_Colour current_rgb;
                    current_rgb.r = cou.country_rgb.r;
                    current_rgb.g = cou.country_rgb.g;
                    current_rgb.b = cou.country_rgb.b;
                    // current_rgb = { 255, 255, 255 };

                    for(auto& reg : cou.country_regs){
                        for(auto& prov : reg.reg_provs){
                            if( 
                                prov.prov_colour.r == r &&
                                prov.prov_colour.g == g &&
                                prov.prov_colour.b == b
                            ){
                                /* First Non Black at 813 x 602 */
                                SDL2_SetPixel(texture, i, j, current_rgb.b, current_rgb.g, current_rgb.r, ALPHA); /* Little endian */
                            }else{
                                /* WARN: Make sure that all provinces have no 0 R, G, B value, else it will crash */
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }

    return SUCCESS;
}

/* TODO: Add mark_outter_borders */
void KENG_MarkInnerBorders(SDL_Surface* src, SDL_Texture* dst){
    if(!src){
        std::printf("Error, source for marking inner borders is incompatible\n");
        return;
    }
    Uint32 black = SDL_MapRGB(src->format, 0, 0, 0);
    int bpp = src->format->BytesPerPixel;
    int pitch = src->pitch;
    Uint8* pixel_array = (Uint8*)src->pixels;

    if(src != NULL){
        for(int i = 0 ; i < src->w ; i++){
            for(int j = 0 ; j < src->h ; j++){
                Uint8 r, g, b;
                Uint32 pixel = *((Uint32*)(pixel_array + j * pitch + i * bpp));

                SDL_GetRGB(pixel, src->format, &r, &g, &b);

                if(pixel == black) continue;
                
                bool is_border = false;

                /* Check Neighours */
                for(int y_off = -1; y_off <= 1; y_off++){
                    for(int x_off = -1; x_off <= 1; x_off++){
                        if(x_off == 0 && y_off == 0) continue; /* Skip current pixel */

                        int x_neighbor = i + x_off;
                        int y_neighbor = j + y_off;

                        /* Check if it is in-bounds */
                        if(x_neighbor >= 0 && x_neighbor < src->w && y_neighbor >= 0 && y_neighbor < src->h){
                            Uint32 neighbor_pixel = *((Uint32*)(pixel_array + y_neighbor * pitch + x_neighbor * bpp));
                            Uint8 r_neighbor, g_neighbor, b_neighbor;
                            SDL_GetRGB(neighbor_pixel, src->format, &r_neighbor, &g_neighbor, &b_neighbor);

                            if(neighbor_pixel != pixel && neighbor_pixel != black){
                                is_border = true;
                                break;
                            }
                        }
                    }
                    if(is_border) break;
                }if(is_border){
                    SDL2_SetPixel(dst, i, j, INNER_BORDER_COLOUR_GS, INNER_BORDER_COLOUR_GS, INNER_BORDER_COLOUR_GS, 130);
                }
            }
        }
    }

    return;
}

void KENG_PrintCountryColours(void){
    for(const auto& cou : KENG_globalCountries){
        std::printf("%s,\t%s\tRGB: <%d,%d,%d>\n",cou.tag.c_str(), cou.country_name.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
    }

    return;
}
