#define SDL_MAIN_HANDLED

#include <cmath>
#include <string>
#include <SDL.h>
#include "tgaimage.h"
#include "sdl-render.hpp"
#include "line-renderer.hpp"

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    
    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& tga_fb = tga.framebuffer();

    // vkr::sdl::SDLTarget sdl(width, height);
    // auto& sdl_fb = sdl.framebuffer();

    mvmath::vec2 a = { 7, 3};
    mvmath::vec2 b = { 12, 37};
    mvmath::vec2 c = { 62, 53};

    vkr::draw_triangle(a, b, c, vkr::COL_GREEN, tga_fb, true);

    tga.present();
    // sdl.run();

    return 0;
}

