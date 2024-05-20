#include "init_map.h"
#include <algorithm>
#include "definitions.aux"

extern SDL_FRect viewport;
extern float map_scale;
extern int map_width;
extern int map_height;

/**
 * @brief renders the map png
 * 
 * @param scale scale of the map
*/
render_capable render_map(float scale);

/**
 * @brief Initialises the starting viewport of the map
 * 
 * @param screen_width x parameter
 * @param screen_height y parameter
*/
void initialise_viewport(float screen_width, float screen_height);
