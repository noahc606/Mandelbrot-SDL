#include "MainLoop.h"
#include <nch/cpp-utils/timer.h>
#include <vector>

MainLoop::MainLoop()
{
    nch::Timer t("MandelPlot", true);
    mandelplot(100);

}
MainLoop::~MainLoop(){}

void MainLoop::tick()
{
    
}


void MainLoop::draw(SDL_Renderer* rend)
{


    for(int ix = 0; ix<512; ix++)
    for(int iy = 0; iy<512; iy++) {
        nch::Color c = cols[ix][iy];
        SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, 255);
        SDL_RenderDrawPoint(rend, pts[ix][iy].x, pts[ix][iy].y);
    }
}

void MainLoop::mandelplot(int maxItrs)
{
    for(int x = 0; x<512; x++) {
        for(int y = 0; y<512; y++) {
            pts[x][y].x = 0;
            pts[x][y].y = 0;
        }
    }

    std::vector<nch::Color> palette;
    for(int i = 0; i<16; i++) {
        nch::Color c;
        c.setFromHSV(360/16*i, 50, 50);
        palette.push_back(c);
    }

    
    double factX = 512./2.47;
    double factY = 512./2.47;
    for(int ix = 0; ix<512; ix++)
    for(int iy = 0; iy<512; iy++) {
        double x0 = ((double)ix)/factX-2.;
        double y0 = ((double)iy)/factX-1.12;
        double x = 0, y = 0;

        int iteration = 0;
        int maxIteration = maxItrs;
        while(x*x+y*y<=4 && iteration<maxIteration) {
            double xtemp = x*x-y*y+x0;
            y = 2*x*y+y0;
            x = xtemp;
            iteration++;
        }

        cols[ix][iy] = palette[iteration%16];
        pts[ix][iy].x = ix;
        pts[ix][iy].y = iy;
    }
}
