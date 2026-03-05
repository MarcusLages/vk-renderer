#pragma once
#include <mvmath.hpp>
#include <render.hpp>
#include <vector>

namespace vkr {
    
    void draw_point(mvmath::vec2 v, vkr::Color col, vkr::IFrameBuffer &fb);
    
    void draw_line(
        mvmath::vec2 a,
        mvmath::vec2 b,
        vkr::Color col,
        vkr::IFrameBuffer &fb
    );
    
    // A 2D vector of lines and their coordinates. E.g. vecs[0] = { vec2 start, vec2 end}
    void draw_lines(
        std::vector< std::vector< mvmath::vec2 > > vecs,
        vkr::Color col,
        vkr::IFrameBuffer &fb
    );
    
    void draw_triangle(
        mvmath::vec2 a,
        mvmath::vec2 b,
        mvmath::vec2 c,
        vkr::Color col,
        vkr::IFrameBuffer &fb,
        bool show_vert = false // If you would like to show the vertex
    );

} // namespace vkr