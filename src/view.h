#ifndef BRST_VIEW_H
#define BRST_VIEW_H

#include <SDL2/SDL.h>

#include "board.h"
#include "hash_map.h"

struct view
{
    struct board* board;
    SDL_Renderer* renderer;
    struct hash_map* texture_map;
};

/**
 * \brief          Create a view of a board
 * \param[in]      board: board structure to wrap in view
 * \param[in]      renderer: Renderer to create texture on
 * \return         Return created view
 */
struct view* view_create(struct board* board, SDL_Renderer* renderer);

/**
 * \brief          Destroys an active view
 * \param[in]      view: view structure
 */
void view_destroy(struct view* view);

/**
 * \brief          Redraw all tiles
 * \param[in]      view: view structure
 */
void view_redraw(struct view* view);

/**
 * \brief          Renders pre-drawn tiles to the screen
 * \param[in]      view: view structure
 */
void view_render(struct view* view);

#endif
