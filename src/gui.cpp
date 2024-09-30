#include "gui.hpp"

PGUI_ActionArguments provAdmDevArgs;
PGUI_ActionArguments provMilDevArgs;
PGUI_ActionArguments provProdDevArgs;
PGUI_Button* adminDev;
PGUI_Button* milDev;
PGUI_Button* prodDev;
PGUI_Item* provInspector;

PGUI_Button* PGUI_UpdateButtonArguments(PGUI_Button* button, PGUI_ArgumentVector newArgs){
    button->actionArgs.arguments = newArgs;
    return button;
}

err_capable init_province_inspector(SDL_Renderer* rnd){

    /* WARN: Overload the path to the correct one */
    PGUI_AssetPath = "ThirdParty/PeakyGUI/assets/";

    // PGUI_ActionArguments provDevArgs = { pguiwIncrementDevelopment, {(void*)provinces[0]}, 1 }; /* Example */

    /* Basic implementation of the GUI (It currently works for one specified province) */
    /* TODO: Make it so that it changes the seen province to what was clicked */
    provAdmDevArgs = { pguiwIncrementAdminDev, { (void*)provinces[0] }, 1 };
    provMilDevArgs = { pguiwIncrementMilDev, { (void*)provinces[0] }, 1 };
    provProdDevArgs = { pguiwIncrementProdDev, { (void*)provinces[0] }, 1 };
    adminDev = PGUI_CreateButtonComplete(provAdmDevArgs, 528, 911, PGUI_Load("mana/admn.png"), renderer);
    milDev = PGUI_CreateButtonComplete(provMilDevArgs, 528, 973, PGUI_Load("mana/mil.png"), renderer);
    prodDev = PGUI_CreateButtonComplete(provProdDevArgs, 528, 1036, PGUI_Load("mana/prod.png"), renderer);
    provInspector = PGUI_CreateItemComplete(0, 901, PGUI_Load("provBox.png"), renderer, {
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

err_capable update_province_inspector(prov* province, SDL_Renderer* rnd){
    if(province == NULL){
        return FAIL;
    }

    PGUI_UpdateButtonArguments(adminDev, { (void*)province });
    PGUI_UpdateButtonArguments(milDev, { (void*)province });
    PGUI_UpdateButtonArguments(prodDev, { (void*)province });

    return SUCCESS;
}
