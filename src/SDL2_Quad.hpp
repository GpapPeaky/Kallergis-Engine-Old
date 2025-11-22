#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_Camera.hpp"

#include <cmath>                /* std::roundf(...) */
#include <algorithm>            /* std::sort(...) */
#include <vector>               /* std::vector<t> */

/* Minimum quad size, affects the LOD */
#define SDL2_MIN_QUAD_SIZE 2

/* Max quads to create */
#define SDL2_MAX_QUADS 32768 * 2

/**
 * Quad object, these will be used to 
 * split uniform colored artifacts inside
 * a bitmap
 */
typedef struct SDL2_Quad{
    SDL_Rect pos;                   /* Quad position and dimensions */
    SDL_Color color;                /* Quad color */
    bool isLeaf;                    /* If the quad is a leaf inside the tree */
    struct SDL2_Quad* children[4]; /* A quad's children */
}SDL2_Quad;

/* Quads created */
extern SDL2_Quad SDL2_Quads[SDL2_MAX_QUADS];

/* Quad count */
extern int SDL2_QuadCount;

/* Debug boolen */
extern bool SDL2_QuadOutlines;

/* TODO */
/**
 * @brief Read a quad file of the name of the image
 * if it doesn't already exist, then generate it.
 * 
 * @param fname File name of the bitmap's generated quads
 * 
 * @returns true if it was read from file
 * and not generated, false if it needs to be generated.
 */
bool SDL2_ReadQuadFile(const char* fname);

/* TODO */
/**
 * @brief Write the generated quads into a quad file
 * 
 * @param fname Name of bitmap, file to store the quad info
 * should be done after merging/post-processing
 */
void SDL2_WriteQuadFile(const char* fname);

/**
 * @brief Checks if 2 colors are the same
 * 
 * @param c1 Color 1
 * @param c2 Color 2
 * @param tolerance Tolerance for color difference
 * 
 * @returns true if the colors are the same
 * false if not
 */
bool SDL2_SameColor(SDL_Color c1, SDL_Color c2, int tolerance);

/**
 * @brief Get the colour of the pixel 
 * 
 * @param src Source to read from
 * @param x X coordinate of pixel
 * @param y Y coordinate of pixel
 * 
 * @returns The found color
 */
SDL_Color SDL2_GetPixel(SDL_Surface* src, int x, int y);

/**
 * @brief Check if a region/artifact is uniform in color
 * 
 * @param src Source to read from 
 * @param x Artifact x coordinate
 * @param y Artifact y coordinate
 * @param w Artifact width
 * @param h Artifact height
 * @param outColor Colour to write
 * 
 * @returns true if the artifact is uniform,
 * false if not
 */
bool SDL2_IsRegionUniform(SDL_Surface* src, int x, int y, int w, int h, SDL_Color* outColor);

/**
 * @brief Recursive quad tree function
 * 
 * @param src Source to read from
 * @param x Artifact x coordinate
 * @param y Artifact y coordinate
 * @param w Artifact width
 * @param h Artifact height
 * 
 * @returns The created quad
 */
SDL2_Quad* SDL2_Quadtree(SDL_Surface* src, int x, int y, int w, int h);

/**
 * @brief Render a quad node along with it's children
 * 
 * @param q Quad to render
 */
void SDL2_RenderQuadNode(SDL2_Quad* q);

/**
 * @brief Check if all the children of a quad
 * have the same colour
 * 
 * @param node Node to check it's children
 * @param outColor Color to check for
 * 
 * @returns true if they do, else false
 */
bool SDL2_AllChildrenLeavesSameColor(SDL2_Quad* node, SDL_Color* outColor);

/**
 * @brief Bottom-up merge, children 'collapse'
 * to the parent if possible
 * 
 * @param node Node to merge the children of 
 */
void SDL2_MergeTree(SDL2_Quad* node);

/* TODO */
/**
 * @brief Generate quads function, includes
 * post-processing
 */
void SDL2_GenerateQuads(void);
