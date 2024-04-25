#ifndef BRST_VIEW_H
#define BRST_VIEW_H

#include <SDL2/SDL.h>

#include "board.h"

struct view
{
    struct board* board;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
};

/**
 * \brief          Create a view of a board
 * \param[in]      board: board structure to wrap in view
 * \param[in]      renderer: Renderer to create texture on
 * \param[in]      width: Width of internal texture
 * \param[in]      height: Height of internal texture
 * \return         Return created view
 */
struct view* view_create(struct board* board, SDL_Renderer* renderer, int width, int height);

/**
 * \brief          Destroys an active view
 * \param[in]      view: view structure
 */
void view_destroy(struct view* view);

/**
 * \brief          Resizes the internal view texture
 * \param[in]      width: Width of new texture
 * \param[in]      height: Height of new texture
 */
void view_resize(struct view* view, int width, int height);

/**
 * \brief          Redraws the internal texture
 * \param[in]      view: view structure
 * \param[in]      x: X pixel coordinate at top left of texture
 * \param[in]      y: Y pixel coordinate at top left of texture
 */
void view_redraw(struct view* view, coord_t x, coord_t y);

#endif
