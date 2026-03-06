#pragma once
#include "render.hpp"

namespace vkr {

    struct FlatRasterizer : public IRenderer {
        bool is_color_rand = true;
        Color triang_col = {};
        
        FlatRasterizer(
            IFrameBuffer& fb,
            Model& model,
            bool is_color_rand = true,
            Color triang_col = {}
        ) : IRenderer(fb, model), is_color_rand(is_color_rand), triang_col(triang_col) {}

        static void draw_point(mvmath::vec2 v, Color col, IFrameBuffer& fb);

        static void draw_triangle(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb,
            bool show_vert = false // If you would like to show the vertex
        );

        static void draw_triangle_scanline(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb,
            bool show_vert = false // If you would like to show the vertex
        );

        void render() override;
    };

}