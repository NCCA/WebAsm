#include <SDL2/SDL.h>
#include <emscripten.h>
#include <cstdlib>
#include <iostream>
#include <array>
#include <random>

struct context
{
    SDL_Renderer *renderer;
    int iteration;

};

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> randInt(-12, 12);
std::uniform_int_distribution<> lifeDist(5, 100);
std::uniform_int_distribution<> colour(10, 255);
std::uniform_int_distribution<> wh(1, 5);

int s_emitterX=200;
int s_emitterY=200;

struct Particle
{
    int xdir; int ydir;
    int m_r,m_g,m_b;
    int life=0;
    SDL_Rect m_rect;
    int maxLife;
    Particle()
    {
      maxLife=lifeDist(gen);
      m_r=colour(gen);
      m_g=colour(gen);
      m_b=colour(gen);
      m_rect.x=s_emitterX;
      m_rect.y=s_emitterY;
      m_rect.h=m_rect.w=wh(gen);
      
      
    }
    ~Particle()=default;
    void update()
    {
        m_rect.x+=xdir;
        m_rect.y+=ydir;
        if( ++life > maxLife)
        {
            life=0;
            maxLife=lifeDist(gen);
            m_r=colour(gen);
            m_g=colour(gen);
            m_b=colour(gen);
            m_rect.x=s_emitterX;
            m_rect.y=s_emitterY;
             m_rect.h=m_rect.w=wh(gen);
        }
    }
    void draw(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, m_r, m_g, m_b, 255);
        SDL_RenderFillRect(renderer, &m_rect );
    }

};

std::array<Particle,500> s_particles;

void mainloop(void *arg)
{

    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP]) 
    {
        s_emitterY-=1;
    }
    else if (state[SDL_SCANCODE_DOWN]) 
    {
        s_emitterY+=1;
    }
    else if (state[SDL_SCANCODE_LEFT]) 
    {
        s_emitterX-=1;
    }
    else if (state[SDL_SCANCODE_RIGHT]) 
    {
        s_emitterX+=1;
    }
    if(s_emitterX <=0) s_emitterX=0;
    else if(s_emitterX >=350) s_emitterX=350;
    if(s_emitterY <=0) s_emitterY=0;
    else if(s_emitterY >=350) s_emitterY=350;


    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
    for(auto &p : s_particles)
    {
      p.update();
      p.draw(renderer);
    }
    std::cout<<"update\n";
    SDL_RenderPresent(renderer);

}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    context ctx;

    SDL_CreateWindowAndRenderer(400, 400, 0, &window, &renderer);
    ctx.renderer = renderer;
    ctx.iteration = 0;

    for(auto &p : s_particles)
    {
        p.xdir=randInt(gen);
        p.ydir=randInt(gen);
    }


    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, &ctx, fps, simulate_infinite_loop);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}