#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../auxf/definitions.aux"

extern SDL_Surface* menu;

/* IDEA: Maybe make a new interface for buttons */
/* TODO: Refactor the code */
typedef struct button{
    SDL_Rect rect;
    const char* text;
    SDL_Surface* img;
}button;

extern std::vector<button> buttons;

void init_menu(std::string filename);

render_capable draw_buttons(void);

button* check_for_button_interaction(void);

