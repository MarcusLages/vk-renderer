#include "line-renderer.hpp"
#include <algorithm>

namespace vkr {

    void draw_point(mvmath::vec2 v, vkr::Color col, vkr::IFrameBuffer &fb) {
        fb.set(std::round(v.x), std::round(v.y), col);
    }
    
    void draw_line(
        mvmath::vec2 a,
        mvmath::vec2 b,
        vkr::Color col,
        vkr::IFrameBuffer &fb
    ) {
        if(a.x > b.x) { // So incrementing actually goes from a to b
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        
        const bool is_transposed = std::abs(b.y - a.y) > b.x - a.x;
        if(is_transposed) {
            // Swap to iterate over the longest line
            std::swap(a.x, a.y);
            std::swap(b.x, b.y);
        }
        
        const float xy_ratio = (b.y - a.y) / (b.x - a.x);
        float y = a.y;
        for(int x = a.x; x <= b.x; x++) {
            if(is_transposed)
                fb.set(std::round(y), x, col);
            else
                fb.set(x, std::round(y), col);
            y += xy_ratio;
        }
    }
    
    // A 2D vector of lines and their coordinates. E.g. vecs[0] = { vec2 start, vec2 end}
    void draw_lines(
        std::vector< std::vector< mvmath::vec2 > > vecs,
        vkr::Color col,
        vkr::IFrameBuffer &fb
    ) {
        // Just playing with c++ functional programming to be more interesting
        std::for_each(
            vecs.begin(), vecs.end(), 
            [&col, &fb](std::vector<mvmath::vec2> line) {
                draw_line(line[0], line[1], col, fb);
            }
        );
    }
    
    void draw_triangle(
        mvmath::vec2 a,
        mvmath::vec2 b,
        mvmath::vec2 c,
        vkr::Color col,
        vkr::IFrameBuffer &fb,
        bool show_vert // If you would like to show the vertex
    ) {
        draw_line(a, b, col, fb);
        draw_line(b, c, col, fb);
        draw_line(c, a, col, fb);

        if(show_vert) {
            const vkr::Color dot_col = (col == vkr::COL_WHITE) ? vkr::COL_BLUE : vkr::COL_WHITE;
            draw_point(a, dot_col, fb);
            draw_point(b, dot_col, fb);
            draw_point(c, dot_col, fb);
        }
    }

} // namespace vkr