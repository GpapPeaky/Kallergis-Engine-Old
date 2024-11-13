#include "PGUI_GUI.hpp"

PGUI_ActionArguments provAdmDevArgs;
PGUI_ActionArguments provMilDevArgs;
PGUI_ActionArguments provProdDevArgs;
PGUI_Button* adminDev;
PGUI_Button* milDev;
PGUI_Button* prodDev;
PGUI_Item* provInspector;

PGUI_Item* countryBar;
PGUI_Item* countryInsignia;
PGUI_Item* countryFlag; /* 263 x 263 png */

PGUI_Item* leaderOverviewBackground;

PGUI_Button* PGUI_UpdateButtonArguments(PGUI_Button* button, PGUI_ArgumentVector newArgs){
    button->actionArgs.arguments = newArgs;
    return button;
}

int PGUI_CreateCountryBar(KENG_country* country, SDL_Renderer* rnd){
    SDL_Surface* cou_flag = IMG_Load("assets/gfx/flags/HER.png");
    if(cou_flag->w != 263 || cou_flag->h != 263){
        std::printf("Wrong size of country flag provided, provide an image with these dimensions: 263 x 263\n");
        return FAIL;
    }

    /* TODO: make the country flag be parsed */
    countryBar = PGUI_CreateItemComplete(0, 0, PGUI_Load("topBar.png"), rnd, {}, PGUI_True);
    countryInsignia = PGUI_CreateItemComplete(0, 0, PGUI_Load("insignia.png"), rnd, {}, PGUI_True);
    countryFlag = PGUI_CreateItemComplete(10, 10, IMG_Load("assets/gfx/flags/HER.png"), rnd, {}, PGUI_True);

    return SUCCESS;
}

int PGUI_CreateProvinceInspector(SDL_Renderer* rnd){
    /* WARN: Overload the path to the correct one */

    // PGUI_ActionArguments provDevArgs = { pguiwIncrementDevelopment, {(void*)provinces[0]}, 1 }; /* Example */

    provAdmDevArgs = { pguiwIncrementAdminDev, { (void*)provinces[0] }, 1 };
    provMilDevArgs = { pguiwIncrementMilDev, { (void*)provinces[0] }, 1 };
    provProdDevArgs = { pguiwIncrementProdDev, { (void*)provinces[0] }, 1 };
    adminDev = PGUI_CreateButtonComplete(provAdmDevArgs, 528, 911 - 400, PGUI_Load("mana/admn.png"), rnd);
    milDev = PGUI_CreateButtonComplete(provMilDevArgs, 528, 973 - 400, PGUI_Load("mana/mil.png"), rnd);
    prodDev = PGUI_CreateButtonComplete(provProdDevArgs, 528, 1036 - 400, PGUI_Load("mana/prod.png"), rnd);
    provInspector = PGUI_CreateItemComplete(0, 901 - 400, PGUI_Load("provBox.png"), rnd, {
        adminDev, milDev, prodDev
    }, PGUI_True);

    // PGUI_ActionArguments incButtonArgs = { PGUI_IncrementWrapper, {} , 0 };
    // PGUI_Button* incButton1 =  PGUI_CreateButtonComplete(incButtonArgs, 0, 0, PGUI_Load("inc.png"), rnd);
    // PGUI_Button* incButton2 =  PGUI_CreateButtonComplete(incButtonArgs, 0, 200, PGUI_Load("inc.png"), rnd);
    // PGUI_Item* switchItem = PGUI_CreateItemComplete(0, 700, PGUI_Load("shieldFrame.png"), rnd, { incButton1, incButton2 }, PGUI_False);

    // PGUI_CreateButtonAsItem(provDevArgs, 500, 500, PGUI_Load("mana/admn.png"), rnd, PGUI_True); /* Faster approach to show just buttons as whole items */

    // /* Button that changes the visibility*/
    // PGUI_ActionArguments switchButtonArgs = { PGUI_ItemVisibilitySwitchWrapper, { switchItem }, 1};
    // PGUI_Button* visibilityButton = PGUI_CreateButtonComplete(switchButtonArgs, 1000, 0, PGUI_Load("butt.png"), rnd);
    // PGUI_CreateItemComplete(0, 0, PGUI_Load("leftbar.png"), rnd, { visibilityButton }, PGUI_True);

    return SUCCESS; /* At some other point it will return an error */
}

int PGUI_UpdateProvinceInspector(prov* province, SDL_Renderer* rnd){
    if(province == NULL){
        return FAIL;
    }

    /* This is a local update for this specific province */
    for(auto& country : KENG_globalCountries){
        for(auto& reg : country.country_regs){
            for(auto& prov : reg.reg_provs){
                if(prov.prov_id == province->prov_id){
                    /* Updates it so that the income is the same as shown in the UI */
                    prov.province_economy.development = province->province_economy.development;
                }
            }
        }
    }

    PGUI_UpdateButtonArguments(adminDev, { (void*)province });
    PGUI_UpdateButtonArguments(milDev, { (void*)province });
    PGUI_UpdateButtonArguments(prodDev, { (void*)province });

    return SUCCESS;
}

int PGUI_CreateCalendar(SDL_Renderer* rnd){
    /* Place holder */
    PGUI_CreateItemComplete(0, 0 , PGUI_Load("inc.png"), rnd, {}, PGUI_True);

    return SUCCESS;
}

int PGUI_CreateCountryLeaderOverview(SDL_Renderer* rnd){
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    leaderOverviewBackground = PGUI_CreateItemComplete(w - 189, 0, PGUI_Load("lo.png"), rnd, {}, PGUI_False);
    printf("Created Leader Overview bar with id %d\n", leaderOverviewBackground->ID);

    return SUCCESS;
}
