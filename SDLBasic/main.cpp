#include <SDL2/SDL.h>
#include <emscripten.h>
#include <cstdlib>
#include <iostream>

struct context
{
    SDL_Renderer *renderer;
    int iteration;
};

void mainloop(void *arg)
{
    static int mode=0;
    static int first=0;

    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;
    
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_R]) {
		mode=0;
        first=0;
	}
    // red background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Rect r;

    if (mode ==0)
    {    
        r.x = 10; 
        r.y = 50;
        r.w = 50;
        r.h = 50;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
        SDL_RenderFillRect(renderer, &r );
        std::cout<<"drawRed();\n";

    }

    if (mode ==1)
    {    
        r.x = 10; 
        r.y = 50;
        r.w = 50;
        r.h = 50;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
        SDL_RenderFillRect(renderer, &r );
        r.x = 80; 
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
        SDL_RenderFillRect(renderer, &r );
        std::cout<<"drawGreen();\n";

    }
    if (mode >=2)
    {    
        r.x = 10; 
        r.y = 50;
        r.w = 50;
        r.h = 50;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
        SDL_RenderFillRect(renderer, &r );
        r.x = 80; 
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
        SDL_RenderFillRect(renderer, &r );
        r.x = 200; 
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255 );
        SDL_RenderFillRect(renderer, &r );
        if(!first)
        {
            std::cout<<"drawBlue();\n";
            first=1;
        }
    }

    SDL_RenderPresent(renderer);
    mode++;
    SDL_Delay(200);

}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(800, 120, 0, &window, &renderer);
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