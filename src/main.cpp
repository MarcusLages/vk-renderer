#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <SDL.h>
#include "tgaimage.h"
#include "sdl-render.hpp"
#include "model.hpp"
#include "line-renderer.hpp"
#include "flat-rasterizer.hpp"

int main(int argc, char** argv) {
    if(argc <= 1) {
        std::cout << "Usage: " + std::string(argv[0]) + " <filename.obj>." ;
        return 1;
    }

    constexpr int width  = 800;
    constexpr int height = 800;
    
    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& tga_fb = tga.framebuffer();

    vkr::sdl::SDLTarget sdl(width, height);
    auto& sdl_fb = sdl.framebuffer();

    vkr::Model model(argv[1]);
    // vkr::LineRenderer render(sdl_fb, model);
    // vkr::LineRenderer tga_render(tga_fb, model);
    // vkr::LineRenderer sdl_render(sdl_fb, model);
    vkr::FlatRasterizer tga_render(tga_fb, model);
    vkr::FlatRasterizer sdl_render(sdl_fb, model);

    mvmath::vec2 a = {7, 3};
    mvmath::vec2 b = {12, 37};
    mvmath::vec2 c = {62, 53};

    // vkr::LineRenderer::draw_triangle(a, b, c, vkr::COL_GREEN, tga_fb, true);
    // vkr::FlatRasterizer::draw_triangle_scanline(a, b, c, vkr::COL_GREEN, tga_fb);

    tga_render.render();
    sdl_render.render();

    tga.present();
    sdl.run();

    return 0;
}

