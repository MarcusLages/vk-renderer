#include <algorithm>
#include "render-utils.hpp"
#include "flat-rasterizer.hpp"

namespace vkr {

    void FlatRasterizer::draw_point(
        mvmath::vec2 v,
        Color col,
        IFrameBuffer& fb
    ) {
        fb.set(std::round(v.x), std::round(v.y), col);
    }

    void FlatRasterizer::draw_triangle(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb,
            bool show_vert // If you would like to show the vertex
    ) {}

    void FlatRasterizer::draw_triangle_scanline(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb,
            bool show_vert // If you would like to show the vertex
    ) {
        ysort(a, b, c);
        const int i_ay = std::round(a.y);
        const int i_by = std::round(b.y);
        const int i_cy = std::round(c.y);

        const float ac_t = ((c.x - a.x) / (c.y - a.y));
        const float ab_t = ((b.x - a.x) / (b.y - a.y));
        const float bc_t = ((c.x - b.x) / (c.y - b.y));

        // float total_height = c.y - a.y;

        if(i_ay != i_by) {
            for(int y = i_ay; y <= i_by; y++) {
                int ac_x = static_cast<int>(std::round(a.x + (y - a.y) * ac_t));
                int ab_x = static_cast<int>(std::round(a.x + (y - a.y) * ab_t));
                auto [min, max] = std::minmax<int>(ab_x, ac_x);
                
                for(int x = min; x <= max; x++) {
                    fb.set(x, y, col);
                    fb.set(x, y, col);
                }
            }
        }

        for(int y = i_by; y <= i_cy; y++) {
            int ac_x = static_cast<int>(std::round(a.x + (y - a.y) * ac_t));
            int bc_x = static_cast<int>(std::round(b.x + (y - b.y) * bc_t));
            auto [min, max] = std::minmax<int>(bc_x, ac_x);
            
            for(int x = min; x <= max; x++) {
                fb.set(x, y, col);
                fb.set(x, y, col);
            }
        }
    }

    void FlatRasterizer::render() {
        std::tuple<int, int> frame = { fb.width(), fb. height() };
        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec2 a = mvmath::central_ortho_project(model.vert(i, 0), model.vert_range, frame);
            mvmath::vec2 b = mvmath::central_ortho_project(model.vert(i, 1), model.vert_range, frame);
            mvmath::vec2 c = mvmath::central_ortho_project(model.vert(i, 2), model.vert_range, frame);

            draw_triangle_scanline(
                a, b, c,
                (is_color_rand) ? get_rand_col() : triang_col, 
                fb
            );
        }
    }

} // namespace vkr
