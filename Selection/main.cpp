#include <SDL2/SDL.h>
#include <emscripten.h>
#include <cstdlib>
#include <iostream>

struct context
{
    SDL_Renderer *renderer;
    int iteration;

};

SDL_Rect r{200,200,50,50};


void mainloop(void *arg)
{

    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;
    
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP]) 
    {
        r.y-=5;
    }
    else if (state[SDL_SCANCODE_DOWN]) 
    {
        r.y+=5;
    }
    else if (state[SDL_SCANCODE_LEFT]) 
    {
        r.x-=5;
    }
    else if (state[SDL_SCANCODE_RIGHT]) 
    {
        r.x+=5;
    }
    if(r.x <=0) r.x=0;
    else if(r.x >=350) r.x=350;
    if(r.y <=0) r.y=0;
    else if(r.y >=350) r.y=350;
    // red background
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect(renderer, &r );

    SDL_RenderPresent(renderer);

}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(400, 400, 0, &window, &renderer);
    std::cout<<"This is a sequence\n";
    context ctx;
    ctx.renderer = renderer;
    ctx.iteration = 0;

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, &ctx, fps, simulate_infinite_loop);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}