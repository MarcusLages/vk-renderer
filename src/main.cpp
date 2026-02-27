#define SDL_MAIN_HANDLED

#include <cmath>
#include <string>
#include <SDL.h>
#include "tgaimage.h"
#include "sdl-render.hpp"

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    
    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& tga_fb = tga.framebuffer();

    vkr::sdl::SDLTarget sdl(width, height);
    auto& sdl_fb = sdl.framebuffer();

    int ax =  5, ay =  5;
    int bx = 12, by = 37;
    int cx = width-6, cy = height-6;

    tga_fb.set(ax, ay, vkr::COL_WHITE);
    tga_fb.set(bx, by, vkr::COL_WHITE);
    tga_fb.set(cx, cy, vkr::COL_WHITE);

    sdl_fb.set(ax, ay, vkr::COL_WHITE);
    sdl_fb.set(bx, by, vkr::COL_WHITE);
    sdl_fb.set(cx, cy, vkr::COL_WHITE);

    tga.present();
    sdl.present();

    return 0;
}

