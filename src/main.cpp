#define SDL_MAIN_HANDLED

#include <cmath>
#include <string>
#include <SDL.h>
#include "tgaimage.h"

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    vkr::tga::TGATarget tga(width, height, vkr::tga::TGAImage::RGB);
    auto& framebuffer = tga.framebuffer();

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, vkr::WHITE);
    framebuffer.set(bx, by, vkr::WHITE);
    framebuffer.set(cx, cy, vkr::WHITE);

    tga.present();
    return 0;
}

