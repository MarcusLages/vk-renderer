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
        std::cout << "Usage: " + std::string(argv[0]) + " <filename.obj>.";
        return 1;
    }

    constexpr int width  = 800;
    constexpr int height = 800;
    
    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& tga_fb = tga.framebuffer();

    vkr::sdl::SDLTarget sdl(width, height);
    auto& sdl_fb = sdl.framebuffer();

    vkr::Model model(argv[1]);
    vkr::LineRenderer tga_line_render(tga_fb, model, vkr::COL_RED);
    vkr::LineRenderer sdl_line_render(sdl_fb, model, vkr::COL_RED);
    vkr::FlatRasterizer tga_flat_render(tga_fb, model);
    vkr::FlatRasterizer sdl_flat_render(sdl_fb, model);

    tga_flat_render.render();
    sdl_flat_render.render();
    // tga_line_render.render();
    // sdl_line_render.render();
    
    // vkr::FlatRasterizer::draw_triangle_scanline(a, b, c, vkr::COL_RED, tga_fb);
    // vkr::FlatRasterizer::draw_triangle_scanline(a, b, c, vkr::COL_RED, sdl_fb);

    tga.present();
    sdl.run();

    return 0;
}

