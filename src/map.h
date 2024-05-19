#include "init_map.h"
#include <algorithm>
#include "definitions.aux"

extern SDL_FRect viewport;
extern float map_scale;
extern int map_width;
extern int map_height;

/**
 * @brief renders the map png
*/
render_capable render_map(void);

/**
 * @brief Initialises the starting viewport of the map
 * 
 * @param screen_width x parameter
 * @param screen_height y parameter
*/
void initialise_viewport(float screen_width, float screen_height);
