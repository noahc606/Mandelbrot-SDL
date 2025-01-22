#pragma once
#include <nch/cpp-utils/color.h>
#include <SDL2/SDL.h>

class MainLoop {
public:
    MainLoop();
    ~MainLoop();

    void tick();
    void draw(SDL_Renderer* rend);

    void mandelplot(int maxItrs);
private:

    SDL_Point pts[512][512];
    nch::Color cols[512][512];
    bool plotted = false;
};