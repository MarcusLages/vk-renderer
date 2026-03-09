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
            IFrameBuffer &fb
    ) {
        mvmath::vec2 min_box = { std::min(std::min(a.x, b.x), c.x), std::min(std::min(a.y, b.y), c.y) };
        mvmath::vec2 max_box = { std::max(std::max(a.x, b.x), c.x), std::max(std::max(a.y, b.y), c.y) };
        float total_area = mvmath::signed_tri_area(a, b, c);

        // TODO: make this concurrent (OpenMP or another thing), can't do it now because of sdl
        // #pragma omp parallel for
        for(float x = min_box.x; x <= max_box.x; x++) {
            for(float y = min_box.y; y <= max_box.y; y++) {
                float alpha = mvmath::signed_tri_area({x, y}, b, c) / total_area;
                float beta = mvmath::signed_tri_area(a, {x, y}, c) / total_area;
                float gamma = mvmath::signed_tri_area(a, b, {x, y}) / total_area;

                if(alpha < 0 || beta < 0 || gamma < 0) continue;
                fb.set(std::round(x), std::round(y), col);
            }
        }
    }

    void FlatRasterizer::draw_triangle_scanline(
            mvmath::vec2 a,
            mvmath::vec2 b,
            mvmath::vec2 c,
            Color col,
            IFrameBuffer &fb
    ) {
        ysort(a, b, c);
        // Used just for equality checking
        const int i_ay = std::round(a.y);
        const int i_by = std::round(b.y);
        const int i_cy = std::round(c.y);

        const float ac_t = ((c.x - a.x) / (c.y - a.y));
        
        if(i_ay != i_by) {
            const float ab_t = ((b.x - a.x) / (b.y - a.y));
            // y is used as float here because of possible precision loss when calculating x
            for(float y = a.y; y <= b.y; y++) {
                int ac_x = std::round(a.x + (y - a.y) * ac_t);
                int ab_x = std::round(a.x + (y - a.y) * ab_t);
                auto [min, max] = std::minmax<int>(ab_x, ac_x);
                
                for(int x = min; x <= max; x++) {
                    fb.set(x, y, col);
                }
            }
        }
        if(i_by != i_cy) {
            const float bc_t = ((c.x - b.x) / (c.y - b.y));
            // y is used as float here because of possible precision loss when calculating x
            for(float y = b.y; y <= c.y; y++) {
                int ac_x = std::round(a.x + (y - a.y) * ac_t);
                int bc_x = std::round(b.x + (y - b.y) * bc_t);
                auto [min, max] = std::minmax<int>(bc_x, ac_x);
                
                for(int x = min; x <= max; x++) {
                    fb.set(x, y, col);
                }
            }
        }

    }

    void FlatRasterizer::render() {
        std::tuple<int, int> frame = { fb.width(), fb. height() };
        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec2 a = mvmath::central_ortho_project(model.vert(i, 0), model.vert_range, frame);
            mvmath::vec2 b = mvmath::central_ortho_project(model.vert(i, 1), model.vert_range, frame);
            mvmath::vec2 c = mvmath::central_ortho_project(model.vert(i, 2), model.vert_range, frame);

            draw_triangle(
                a, b, c,
                (is_color_rand) ? get_rand_col() : triang_col, 
                fb
            );
        }
    }

    void FlatRasterizer::render_scanline() {
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
