#include "SDL2_Font.hpp"

SDL_Color text_colour = { 255, 255, 255};
SDL_Color text_colour_bg = {0, 0, 0};
SDL_Surface* text = NULL;
SDL_Texture* txt = NULL;
SDL_Texture* b_txt = NULL;
TTF_Font* prov_inspector_font = NULL;
TTF_Font* top_bar_font = NULL;
SDL_Rect rect;
SDL_Rect b_rect;
SDL_Rect c_rect;

err_capable SDL2_CreateFont(void){

    TTF_Init(); /* Initialise */

    prov_inspector_font = TTF_OpenFont("assets/gfx/font/constanb.ttf", PROVINCE_INSPECTOR_FONT_SIZE);
    if(!prov_inspector_font){
        std::printf("FONT: %s\n ", SDL_GetError());
        return FAIL;
    }

    top_bar_font = TTF_OpenFont("assets/gfx/font/constanb.ttf", TOP_BAR_FONT_SIZE);
    if(!top_bar_font){
        std::printf("FONT: %s\n ", SDL_GetError());
        return FAIL;
    }

    return SUCCESS;
}

render_capable SDL2_RenderText(std::string msg, int x, int y, TTF_Font* font){
    text = TTF_RenderUTF8_Solid(font, msg.c_str(), text_colour);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    txt = SDL_CreateTextureFromSurface(renderer, text);
    if(!txt){
        std::printf("%s\n ", SDL_GetError());
    }

    SDL_FreeSurface(text);

    text = TTF_RenderUTF8_Solid(font, msg.c_str(), text_colour_bg);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    b_txt = SDL_CreateTextureFromSurface(renderer, text);
    if(!b_txt){
        std::printf("%s\n ", SDL_GetError());
    }

    SDL_FreeSurface(text);

    rect.x = x;
    rect.y = y;
    rect.h = text->h;
    rect.w = text->w;

    b_rect.x = rect.x + 2;
    b_rect.y = rect.y + 2;
    b_rect.h = text->h + 2;
    b_rect.w = text->w + 2;

    c_rect.x = rect.x - 2;
    c_rect.y = rect.y - 2;
    c_rect.h = text->h;
    c_rect.w = text->w;

    SDL_RenderCopy(renderer, b_txt, NULL, &c_rect);
    SDL_RenderCopy(renderer, b_txt, NULL, &b_rect);
    SDL_RenderCopy(renderer, txt, NULL, &rect);

    SDL_DestroyTexture(b_txt);
    SDL_DestroyTexture(txt);
}

render_capable SDL2_RenderOnMouseHover(void){
    return;
}

render_capable SDL2_RenderCountryStats(cou* country){
    if(country == NULL){
        return;
    }

    std::string bank = SDL2_FormatFloat(country->balance);
    std::string men = std::to_string(country->manpower);
    std::string stability = std::to_string(country->stab);
    std::string pops_string;
    uint pops = 0;

    for(auto& regions : country->country_regs){
        for(auto& prov : regions.reg_provs){
            pops += prov.province_economy.local_goods.population;
        }
    }

    pops_string = std::to_string(pops);

    SDL2_RenderText(bank, 306, 41, top_bar_font);
    SDL2_RenderText(men, 572, 41, top_bar_font);
    SDL2_RenderText(stability, 777, 41, top_bar_font);
    SDL2_RenderText(pops_string, 995, 41, top_bar_font);
    
    return;
}

render_capable SDL2_RenderProvinceInfo(prov* province){
    if(province == NULL){
        // std::printf("Error: province NULL at render_province_info\n");
        return; /* if NULL, shows nothing */
    }
    /* Part of the Province Inspector */

    std::string province_name = province->prov_name; /* string */
    std::string province_reg;
    for(auto& reg : regions){
        if(reg.reg_id == province->region){
            province_reg = reg.reg_name; /* string */
        }
    }
    /* FIXME: Make this be like 123.23k */
    std::string province_pop = "Pops: " + std::to_string(province->province_economy.local_goods.population / 1000) + "k"; /* int */
    std::string province_admin = std::to_string(province->province_economy.development.admin); /* int */
    std::string province_mil = std::to_string(province->province_economy.development.mil); /* int */
    std::string province_prod = std::to_string(province->province_economy.development.prod); /* int */

    float income = I(province->province_economy);
    std::string province_income = "Income: " + SDL2_FormatFloat(income);
    float production = GP(province->province_economy);
    std::string province_goods_produced = "Production: " + SDL2_FormatFloat(production);

    std::string province_good = "Produce: " + std::string(goods_names[province->province_economy.local_goods.good]); /* const char* */

    SDL_Texture* province_good_texture = goods_textures[province->province_economy.local_goods.good]; /* This is fine */
    SDL_Rect province_good_rect = { 362, 1017 - 400, GOOD_SIZE, GOOD_SIZE }; /* rectangle for rendering the province's good */

    /* Renditions */
    /* TODO: Check for memory leaks */
    SDL2_RenderText(province_name, 17, 921 - 400, prov_inspector_font);
    SDL2_RenderText(province_reg, 17, 957 - 400, prov_inspector_font);
    
    SDL2_RenderText(province_pop, 17, 1031 - 400, prov_inspector_font);
    SDL2_RenderText(province_admin, 474, 927 - 400, prov_inspector_font);
    SDL2_RenderText(province_mil, 474, 974 - 400, prov_inspector_font);
    SDL2_RenderText(province_prod, 474, 1025 - 400, prov_inspector_font);

    SDL2_RenderText(province_income, 219, 942 - 400, prov_inspector_font);
    SDL2_RenderText(province_goods_produced, 200, 1024 - 400, prov_inspector_font);

    SDL2_RenderText(province_good, 310, 1000 - 400, prov_inspector_font);

    SDL_RenderCopy(renderer, province_good_texture, NULL, &province_good_rect);

    return;
}

std::string SDL2_FormatFloat(float value){
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}

/* FIXME: PARSE A INFO FROM ONE FUCKING SOURCE JESUS PLEASE */
