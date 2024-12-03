#include "KENG_City.hpp"

std::unordered_map<int, KENG_City> KENG_Cities;

static int KENG_GenerateCityID(void){
    static int currentID = 0;
    return currentID++;
}

int KENG_CreateCity(int x, int y, std::string cityName, SDL_Surface* citySurface, SDL_Renderer* rnd){
    if(citySurface == NULL){
        printf("City surface provided is null\n");
        return FAIL;
    }

    KENG_City newCity;

    newCity.cityRect.x = x;
    newCity.cityRect.y = y;
    newCity.cityRect.w = citySurface->w;
    newCity.cityRect.h = citySurface->h;

    #ifdef CITY_PRINT_DEBUG
        std::printf("Created city surface <%d,%d>\n", newCity.cityRect.w, newCity.cityRect.h);
    #endif

    newCity.cityName = cityName;
    newCity.citySurface = citySurface;
    newCity.cityTexture = SDL_CreateTextureFromSurface(rnd, citySurface);
    if(newCity.cityTexture == NULL){
        printf("Failed to create city texture\n");
        return FAIL;
    }

    KENG_Cities[KENG_GenerateCityID()] = newCity; /* Add to the unordered map */

    return SUCCESS;    
}

void SDL2_RenderCities(SDL_Renderer* rnd, camera cam){
    SDL_Rect zoomRectangle;

    for(const auto& pair : KENG_Cities){
        const KENG_City& city = pair.second;

        zoomRectangle.x = (city.cityRect.x - cam.rect.x) * cam.zoom;
        zoomRectangle.y = (city.cityRect.y - cam.rect.y) * cam.zoom;
        zoomRectangle.w = city.cityRect.w * cam.zoom; /* Avoid rounding issues */
        zoomRectangle.h = city.cityRect.h * cam.zoom;
        
        if(SDL_RenderCopy(rnd, city.cityTexture, NULL, &zoomRectangle) != 0){
            printf("Failed to render city texture: %s\n", SDL_GetError());
            continue;
        }

        int textX = zoomRectangle.x + 10; /* Position the text on the right of the city pin */
        int textY = zoomRectangle.y;
        SDL2_RenderText(city.cityName.c_str(), textX, textY, city_font);
    }

    return;
}
