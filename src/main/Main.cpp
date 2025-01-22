

#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <nch/sdl-utils/main-loop-driver.h>
#include "MainLoop.h"

MainLoop ml;
int lastSec = -999;
int counter = 50;

void tick()
{
    int thisSec = std::time(NULL);
    if(thisSec!=lastSec) {
        lastSec = thisSec;

        counter++;
        //ml.mandelplot(counter);
        
        std::string gpi = nch::MainLoopDriver::getPerformanceInfo();
        if(gpi!="???null???") {
            std::printf("%s\n", gpi.c_str());
        }
    }

    ml.tick();
}

void draw(SDL_Renderer* rend)
{
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, NULL);

    ml.draw(rend);

    SDL_RenderPresent(rend);
}

int main(int argc, char** argv)
{
    SDL_Window* win = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_SetWindowResizable(win, SDL_TRUE);
    
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
    
    SDL_ShowWindow(win);

    nch::MainLoopDriver mld(rend, &tick, 40, &draw, 200);
}