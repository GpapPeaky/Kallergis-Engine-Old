#include "gui.hpp"
#include "pgui_function_overloads.hpp"

err_capable init_pgui(SDL_Renderer* rnd){

    /* WARN: Overload the path to the correct one */
    PGUI_AssetPath = "ThirdParty/PeakyGUI/assets/";

    PGUI_ActionArguments provDevArgs = { pguiwIncrementDevelopment, {(void*)provinces[0]}, 1 }; /* Example */

    PGUI_ActionArguments incButtonArgs = { PGUI_IncrementWrapper, {} , 0 };
    PGUI_Button* incButton1 =  PGUI_CreateButtonComplete(incButtonArgs, 0, 0, PGUI_Load("inc.png"), rnd);
    PGUI_Button* incButton2 =  PGUI_CreateButtonComplete(incButtonArgs, 0, 200, PGUI_Load("inc.png"), rnd);
    PGUI_Item* switchItem = PGUI_CreateItemComplete(0, 700, PGUI_Load("shieldFrame.png"), rnd, { incButton1, incButton2 }, PGUI_False);

    PGUI_CreateButtonAsItem(provDevArgs, 500, 500, PGUI_Load("mana/admn.png"), rnd, PGUI_True); /* Faster approach to show just buttons as whole items */

    /* Button that changes the visibility*/
    PGUI_ActionArguments switchButtonArgs = { PGUI_ItemVisibilitySwitchWrapper, { switchItem }, 1};
    PGUI_Button* visibilityButton = PGUI_CreateButtonComplete(switchButtonArgs, 1000, 0, PGUI_Load("butt.png"), rnd);
    PGUI_CreateItemComplete(0, 0, PGUI_Load("leftbar.png"), rnd, { visibilityButton }, PGUI_True);

    return SUCCESS; /* At some other point it will return an error */
}
