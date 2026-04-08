#include "camera-rasterizer.hpp"
#include "render-utils.hpp"

namespace vkr {

    // Uses z-buffer
    void CameraRasterizer::draw_triangle(
        mvmath::vec3 a,
        mvmath::vec3 b,
        mvmath::vec3 c,
        Color col
    ) {
        // TODO
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

    void CameraRasterizer::render() {
        std::tuple<int, int> frame = {
            fb.width() * FRAME_PERCENTAGE, fb.height() * FRAME_PERCENTAGE
        };
        for(int i = 0; i < model.faces_len(); i++) {
            // TODO: PIPELINE
            mvmath::vec3 a = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 0), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);
            mvmath::vec3 b = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 1), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);
            mvmath::vec3 c = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 2), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);

            draw_triangle(
                a, b, c,
                (is_color_rand) ? get_rand_col() : tri_col
            );
        }
    }
}