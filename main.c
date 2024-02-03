#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

struct {
    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool quit;
} state;


int main(int argc, char *argv[])
{

    state.window = NULL;
    state.renderer = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    state.window = SDL_CreateWindow("fps", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(NULL == state.window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == state.renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
        SDL_RenderCopyEx(
            state.renderer,
            state.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL);
        SDL_RenderPresent(state.renderer);

    while(true) {
        state.pixels[0] = 0xFF0000FF;
    }






    statut = EXIT_SUCCESS;
    SDL_Delay(3000);

Quit:
    if(NULL != state.renderer)
        SDL_DestroyRenderer(state.renderer);
    if(NULL != state.window)
        SDL_DestroyWindow(state.window);
    SDL_Quit();
    return statut;
}
