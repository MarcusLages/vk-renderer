#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <SDL.h>
#include "tgaimage.h"
#include "sdl-render.hpp"
#include "model.hpp"
#include "line-renderer.hpp"
#include "flat-rasterizer.hpp"
#include "camera-rasterizer.hpp"

int main(int argc, char** argv) {
    if(argc <= 1) {
        std::cout << "Usage: " + std::string(argv[0]) + " <filename.obj>.";
        return 1;
    }

    constexpr int width  = 800;
    constexpr int height = 800;
    
    vkr::Model model(argv[1]);
    model.transform.rotate({mvmath::deg_to_rad(10), mvmath::deg_to_rad(15), 0});

    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& tga_fb = tga.framebuffer();

    vkr::sdl::SDLTarget sdl(width, height);
    auto& sdl_fb = sdl.framebuffer();

    //* RENDERERS

    // LineRenderer
    // vkr::LineRenderer tga_line_render(tga_fb, model, vkr::COL_RED);
    // vkr::LineRenderer sdl_line_render(sdl_fb, model, vkr::COL_RED);
    // tga_line_render.render();
    // sdl_line_render.render();

    // FlatRenderer
    // vkr::FlatRasterizer tga_flat_render(tga_fb, model);
    // vkr::FlatRasterizer sdl_flat_render(sdl_fb, model);
    // tga_flat_render.render();
    // sdl_flat_render.render();

    // CameraRenderer
    const float fov = 90;
    vkr::PerspCamera cam(vkr::Camera::STD_POS, width, height, fov);
    // vkr::OrthoCamera cam(vkr::Camera::STD_POS, width, height, fov);
    vkr::CameraRasterizer tga_cam_render(tga_fb, model, cam);
    vkr::CameraRasterizer sdl_cam_render(sdl_fb, model, cam);
    tga_cam_render.render();
    sdl_cam_render.render();

    tga.present();
    sdl.run();

    return 0;
}

