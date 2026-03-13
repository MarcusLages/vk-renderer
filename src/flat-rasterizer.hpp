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
            IFrameBuffer &fb
        );

        // Uses the z-buffer when rendering
        static void draw_triangle_zbuf(
            mvmath::vec3 a,
            mvmath::vec3 b,
            mvmath::vec3 c,
            Color col,
            IFrameBuffer &fb
        );

        // Renders the z-buffer (depth buffer) in grayscale
        static void draw_triangle_depth(
            mvmath::vec3 a,
            mvmath::vec3 b,
            mvmath::vec3 c,
            IFrameBuffer &fb
        );

        static void draw_triangle_scanline(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb
        );

        void render() override;
        void render_depth();
        void render_scanline();
    };

}