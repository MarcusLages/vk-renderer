#pragma once
#include <vector>
#include "mvmath.hpp"
#include "render.hpp"

namespace vkr {

    struct LineRenderer : public IRenderer {
        static constexpr Color DEF_LINE_COL = COL_WHITE;
        Color line_col;

        LineRenderer(IFrameBuffer& fb, Model& model, Color line_col = DEF_LINE_COL) 
            : IRenderer(fb, model) {}

        static void draw_point(mvmath::vec2 v, vkr::Color col, vkr::IFrameBuffer &fb);

        static void draw_line(
            mvmath::vec2 a,
            mvmath::vec2 b,
            vkr::Color col,
            vkr::IFrameBuffer &fb
        );

        static void draw_line_bresenham(
            mvmath::vec2 a,
            mvmath::vec2 b,
            vkr::Color col,
            vkr::IFrameBuffer &fb
        );
        
        // A 2D vector of lines and their coordinates. E.g. vecs[0] = { vec2 start, vec2 end}
        static void draw_lines(
            std::vector< std::vector< mvmath::vec2 > > vecs,
            vkr::Color col,
            vkr::IFrameBuffer &fb
        );
        
        static void draw_triangle(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            vkr::Color col,
            vkr::IFrameBuffer &fb,
            bool show_vert = false // If you would like to show the vertex
        );
        
        void render() override;
    };
    

} // namespace vkr