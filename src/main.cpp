#include <cmath>
#include "tgaimage.h"

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, TGAColor(white));
    framebuffer.set(bx, by, TGAColor(white));
    framebuffer.set(cx, cy, TGAColor(white));

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

