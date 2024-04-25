#include <stdio.h>
#include <SDL2/SDL.h>

#include "board.h"
#include "view.h"

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("Failed to initialize SDL\n");
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("brst",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1024,
                                          576,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Failed to create window\n");
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        printf("Failed to create renderer\n");
    }

    struct board* board = board_create();
    struct view* view = view_create(board, renderer, 1024 / 16, 576 / 16);

    board_set_pixel(board, 10, 10, PIXEL_WIRE);
    board_set_pixel(board, 20, 10, PIXEL_AND);
    board_set_pixel(board, 10, 20, PIXEL_OR);
    board_set_pixel(board, 20, 20, PIXEL_NOT);

    view_redraw(view, 0, 0);

    SDL_Event event;
    int running = 1;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, view->texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    view_destroy(view);
    board_destroy(board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
