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
        mvmath::vec2 min_box = { std::round(std::min(std::min(a.x, b.x), c.x)), std::round(std::min(std::min(a.y, b.y), c.y)) };
        mvmath::vec2 max_box = { std::round(std::max(std::max(a.x, b.x), c.x)), std::round(std::max(std::max(a.y, b.y), c.y)) };
        float total_area = mvmath::signed_tri_area(a, b, c);

        // Less than one because we are skipping triangles facing the wrong direction
        // or that have an area less than 1 pixel
        if(total_area < 1) return;

        // TODO: make this concurrent (OpenMP or another thing), can't do it now because of sdl
        // #pragma omp parallel for
        for(float x = min_box.x; x <= max_box.x; x++) {
            for(float y = min_box.y; y <= max_box.y; y++) {
                mvmath::vec2 p = {x, y};
                float alpha = mvmath::signed_tri_area(p, b, c) / total_area;
                float beta = mvmath::signed_tri_area(a, p, c) / total_area;
                float gamma = mvmath::signed_tri_area(a, b, p) / total_area;

                if(alpha < 0 || beta < 0 || gamma < 0) continue;
                fb.set(x, y, col);
            }
        }
    }

    // Uses the z-buffer when rendering
    void FlatRasterizer::draw_triangle_zbuf(
            mvmath::vec3 a,
            mvmath::vec3 b,
            mvmath::vec3 c,
            Color col,
            IFrameBuffer &fb
    ) {
        mvmath::vec2 a_v2 = {a.x, a.y};
        mvmath::vec2 b_v2 = {b.x, b.y};
        mvmath::vec2 c_v2 = {c.x, c.y};
        mvmath::vec2 min_box = { std::round(std::min(std::min(a.x, b.x), c.x)), std::round(std::min(std::min(a.y, b.y), c.y)) };
        mvmath::vec2 max_box = { std::round(std::max(std::max(a.x, b.x), c.x)), std::round(std::max(std::max(a.y, b.y), c.y)) };
        float total_area = mvmath::signed_tri_area(a_v2, b_v2, c_v2);

        // Less than one because we are skipping triangles facing the wrong direction
        // or that have an area less than 1 pixel
        if(total_area < 1) return;

        // TODO: make this concurrent (OpenMP or another thing), can't do it now because of sdl
        // #pragma omp parallel for
        for(float x = min_box.x; x <= max_box.x; x++) {
            for(float y = min_box.y; y <= max_box.y; y++) {
                mvmath::vec2 p = {x, y};
                float alpha = mvmath::signed_tri_area(p, b_v2, c_v2) / total_area;
                float beta = mvmath::signed_tri_area(a_v2, p, c_v2) / total_area;
                float gamma = mvmath::signed_tri_area(a_v2, b_v2, p) / total_area;
                
                if(alpha < 0 || beta < 0 || gamma < 0) continue;
                // TODO: make it so it skips the whole row/column if not
                if(!fb.is_in_bounds(x, y)) continue;

                float z = a.z * alpha + b.z * beta + c.z * gamma;
                if(z > fb.get_z(x, y)) continue;

                fb.set(x, y, z, col);
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
        std::tuple<int, int> frame = { fb.width() - 1, fb. height() - 1 };
        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec3 a = mvmath::central_ortho_project_z(model.vert(i, 0), model.vert_range, frame);
            mvmath::vec3 b = mvmath::central_ortho_project_z(model.vert(i, 1), model.vert_range, frame);
            mvmath::vec3 c = mvmath::central_ortho_project_z(model.vert(i, 2), model.vert_range, frame);

            draw_triangle_zbuf(
                a, b, c,
                (is_color_rand) ? get_rand_col() : tri_col, 
                fb
            );
        }
    }

    void FlatRasterizer::render_scanline() {
        std::tuple<int, int> frame = { fb.width() - 1, fb. height() - 1 };
        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec2 a = mvmath::central_ortho_project(model.vert(i, 0), model.vert_range, frame);
            mvmath::vec2 b = mvmath::central_ortho_project(model.vert(i, 1), model.vert_range, frame);
            mvmath::vec2 c = mvmath::central_ortho_project(model.vert(i, 2), model.vert_range, frame);

            draw_triangle_scanline(
                a, b, c,
                (is_color_rand) ? get_rand_col() : tri_col, 
                fb
            );
        }
    }

} // namespace vkr
