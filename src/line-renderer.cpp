#include <algorithm>
#include "line-renderer.hpp"

namespace vkr {

    void LineRenderer::draw_point(mvmath::vec2 v, vkr::Color col, vkr::IFrameBuffer &fb) {
        fb.set(std::round(v.x), std::round(v.y), col);
    }
    
    void LineRenderer::draw_line(
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
        for(int x = std::round(a.x); x <= b.x; x++) {
            if(is_transposed)
                fb.set(std::round(y), x, col);
            else
                fb.set(x, std::round(y), col);
            y += xy_ratio;
        }
    }
    
    void LineRenderer::draw_line_bresenham( // It's going to be a bit slower since I use float coord
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
        
        const float y_steps = std::abs(b.y - a.y);
        const float x_steps = std::abs(b.x - a.x);
        int y = std::round(a.y);
        int err = 0;
        for(int x = std::round(a.x); x <= b.x; x++) {
            if(is_transposed)
                fb.set(y, x, col);
            else
                fb.set(x, y, col);

            err += 2 * y_steps;
            y += (b.y > a.y ? 1 : -1) * (err > b.x - a.x); // int bool hack by ssloy
            err -= (2 * x_steps) * (err > b.x - a.x);
        }
    }
    
    // A 2D vector of lines and their coordinates. E.g. vecs[0] = { vec2 start, vec2 end}
    void LineRenderer::draw_lines(
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
    
    void LineRenderer::draw_triangle(
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

    // Orthogonal projection to the center of the screen from a model
    mvmath::vec2 ortho_project(
        mvmath::vec3 v,
        std::tuple<float, float> v_range,
        std::tuple<int, int> frame
    ) {
        auto [min, max] = v_range;
        auto [width, height] = frame;

        // We use height for both x and y so the model  fits on the center
        // square on the screen and it doesn't get stretched
        return {
            (height / (max - min)) * v.x + width / 2.f,
            (height / (max - min)) * v.y + height / 2.f
        };
    }

    void LineRenderer::render() {
        std::tuple<int, int> frame = { fb.width(), fb. height() };
        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec2 a = ortho_project(model.vert(i, 0), model.vert_range, frame);
            mvmath::vec2 b = ortho_project(model.vert(i, 1), model.vert_range, frame);
            mvmath::vec2 c = ortho_project(model.vert(i, 2), model.vert_range, frame);

            draw_triangle(a, b, c, line_col, fb);
        }
    }

} // namespace vkr