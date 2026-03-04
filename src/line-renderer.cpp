#include "line-renderer.hpp"
#include <algorithm>

namespace vkr {

    void draw_point(mvmath::vec2 v, vkr::Color col, vkr::IFrameBuffer &fb) {
        fb.set(v.x, v.y, col);
    }
    
    void draw_line(
        mvmath::vec2 a,
        mvmath::vec2 b,
        vkr::Color col,
        vkr::IFrameBuffer &fb
    ) {
        for(float t = 0; t <= 1.0; t += .02) {
            float x = a.x + t * (b.x - a.x);
            float y = a.y + t * (b.y - a.y);
            fb.set(x, y, col); // Random colour
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