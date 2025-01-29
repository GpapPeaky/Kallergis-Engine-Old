#include "SDL2_TextureFonts.hpp"

SDL2_TextureFont* BSC_CWWBFont;
SDL2_TextureFont* BSC_ItemHoverFont;
SDL2_TextureFont* BSC_ItemIncFont;
SDL2_TextureFont* BSC_ItemDecFont;

SDL2_TextureFont* SDL2_CreateTextureFont(const char* filename, unsigned int fontSize){
    SDL2_TextureFont* newFont = new SDL2_TextureFont;

    newFont->font.surface = IMG_Load(filename);
    if(newFont->font.surface == NULL){ std::fprintf(stderr, "Cannot create font surface\n"); return NULL; }

    newFont->font.texture = SDL_CreateTextureFromSurface(SDL2_Rnd, newFont->font.surface);
    if(newFont->font.texture == NULL){ std::fprintf(stderr, "Cannot create font texture\n"); return NULL; }

    newFont->letterSpace = 1;
    newFont->sheetWidth = newFont->font.surface->w;
    newFont->sheetHeight = newFont->font.surface->h;
    SDL_FreeSurface(newFont->font.surface);
    newFont->fontSize = fontSize;

    return newFont;
}

SDL_Rect SDL2_MapCharacterToTextureFont(SDL2_TextureFont* font, char c){
    /**
     * @note Letters:
     * 
     * ASCII: A -> 65 | Z -> 90 
     * ASCII: a -> 97 | z -> 122
     * Relative difference from capital letters: 97 - 65 = 32
     * 
     * @note Numbers:
     * 
     * ASCII: 0 -> 48 | 9 -> 57
     * 
     * @note Special Characters:
     * 
     * ASCII: , -> 44
     * ASCII: - -> 45
     * ASCII: space -> 32
     * ASCII: ! -> 33
     * 
     * @note Sheet Coordinates:
     * 
     * (char = x,y) 
     * 
     * a = 0,0
     * b = 1,0
     * c = 2,0
     * d = 3,0
     * e = 4,0
     * f = 5,0
     * g = 6,0
     * h = 7,0
     * i = 0,1
     * j = 0,2
     * k = 0,3
     * l ...
     * z = 1,4
     * 
     * Numbers:
     * 
     * 0 = 2,3
     * 1 = 3,3
     * 2 ...
     * 9 = 4,4
     * 
     * - = 5,4
     * , = 6,4
     * ! = 7,4
     * Space = 8,4
     * 
     */

    /* Rectangle to return, the size of each character is 9x9 px */
    SDL_Rect sourceRect;
    sourceRect.w = 8;
    sourceRect.h = 8;

    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        char upperChar = (c >= 'a' && c <= 'z') ? c - 32 : c;

        int idx = upperChar - 'A';
        sourceRect.x = (idx % 8) * sourceRect.w; /* char Width */
        sourceRect.y = (idx / 8) * sourceRect.h; /* char Height */
    }else if(c >= '0' && c <= '9'){
        int idx = (c - '0') + 26;
        sourceRect.x = (idx % 8) * sourceRect.w; /* char Width */
        sourceRect.y = (idx / 8) * sourceRect.h; /* char Height */
    }else{
        switch(c){
            case '-': sourceRect.x = 4 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break;
            case '+': sourceRect.x = 4 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break; /* WARN: For the stat fonts only */
            case ',': sourceRect.x = 5 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break;
            case '.': sourceRect.x = 5 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break; /* WARN: For the stat fonts only */
            case '!': sourceRect.x = 6 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break;
            case '%': sourceRect.x = 6 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break; /* WARN: For the stat fonts only */
            case ' ': sourceRect.x = 7 * sourceRect.w; sourceRect.y = 4 * sourceRect.h; break;
            default:  sourceRect.x = 0; sourceRect.y = 0; break;  /* Return top-left corner for unsupported chars */
        }
    }

    return sourceRect;
}

void SDL2_RenderFontCharacter(SDL2_TextureFont* font, char c, int x, int y){
    if(font == NULL){ std::fprintf(stderr, "Null font\n"); return; }
    SDL_Rect src = SDL2_MapCharacterToTextureFont(font, c);
    SDL_Rect dst = { x, y, static_cast<int>(font->fontSize), static_cast<int>(font->fontSize) };

    SDL_RenderCopy(SDL2_Rnd, font->font.texture, 
    &src, &dst);

    return;
}

void SDL2_RenderFontText(SDL2_TextureFont* font, const char* str, int x, int y){
    for(int i = 0 ; str[i] != '\0' ; i++){
        SDL2_RenderFontCharacter(font, str[i], x + i * (font->letterSpace + font->fontSize), y);
    }

    return;
}

std::string SDL2_2PointFloatString(float value){
    int integerPart = static_cast<int>(value);
    float decimalPart = value - integerPart; 
    int decimalAsInt = std::abs(static_cast<int>(decimalPart * 100));

    return std::to_string(integerPart) + "." + std::to_string(decimalAsInt);
}

void BSC_RenderStat(const char* statName, float stat, int x, int y, bool perFlag) {
    if (std::fabs(stat) < BSC_EPSILON) return; /* If 0 do not enter */

    /* Determine font and sign based on stat value */
    SDL2_TextureFont* font = (stat > 0) ? BSC_ItemIncFont : BSC_ItemDecFont;
    std::string sign = (stat > 0) ? "+" : "-";

    /* Building the string */
    std::string statString;
    statString = std::string(statName) + " " + sign + SDL2_2PointFloatString(std::fabs(stat));
    if(perFlag){
        statString += "%";
    }

    SDL2_RenderFontText(font, statString.c_str(), x, y);

    return;
}
