#include <cmath>
#include <string>
#include "tgaimage.h"

const std::string filename = "framebuffer.tga";

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    vkr::TGAImage framebuffer(width, height, vkr::TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, vkr::WHITE);
    framebuffer.set(bx, by, vkr::WHITE);
    framebuffer.set(cx, cy, vkr::WHITE);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

