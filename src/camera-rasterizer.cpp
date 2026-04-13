#include <algorithm>
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
        mvmath::vec2 a_v2 = a.to_vec2();
        mvmath::vec2 b_v2 = b.to_vec2();
        mvmath::vec2 c_v2 = c.to_vec2();

        auto [min_p, max_p] = mvmath::vec2::bound_box(a_v2, b_v2, c_v2);
        // Clamping and rounding min/max points
        min_p.x = std::clamp(std::round(min_p.x), 0.f, static_cast<float>(fb.width()));
        min_p.y = std::clamp(std::round(min_p.y), 0.f, static_cast<float>(fb.width()));

        max_p.x = std::clamp(std::round(max_p.x), 0.f, static_cast<float>(fb.width()));
        max_p.y = std::clamp(std::round(max_p.y), 0.f, static_cast<float>(fb.width()));

        float total_area = mvmath::signed_tri_area(a_v2, b_v2, c_v2);

        // Less than one because we are skipping triangles facing the wrong direction
        // or that have an area less than 1 pixel
        if(total_area < 1) return;

        // TODO: make this concurrent (OpenMP or another thing), can't do it now because of sdl
        // #pragma omp parallel for
        for(float x = min_p.x; x <= max_p.x; x++) {
            for(float y = min_p.y; y <= max_p.y; y++) {
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

    void CameraRasterizer::render_no_mat() {
        std::tuple<int, int> frame = {
            fb.width() * FRAME_PERCENTAGE, fb.height() * FRAME_PERCENTAGE
        };
        for(int i = 0; i < model.faces_len(); i++) {
            // TODO: Clipping next
            mvmath::vec3 a = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 0), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);
            mvmath::vec3 b = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 1), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);
            mvmath::vec3 c = mvmath::central_ortho_project_z(mvmath::persp_project(model.vert(i, 2), {0, 0, 2}, M_PI / 2, 2), model.vert_range, frame);

            draw_triangle(
                a, b, c,
                (is_color_rand) ? get_rand_col() : tri_col
            );
        }
    }
    
    void CameraRasterizer::render() {
        // cam.set_model(model.mat()); // TODO: add model transform to Model
        mvmath::mat4 proj = cam.project();
        mvmath::mat4 vp = cam.viewport();

        for(int i = 0; i < model.faces_len(); i++) {
            mvmath::vec4 va = mvmath::vec4(model.vert(i, 0), 1);
            mvmath::vec4 vb = mvmath::vec4(model.vert(i, 1), 1);
            mvmath::vec4 vc = mvmath::vec4(model.vert(i, 2), 1);

            mvmath::vec4 pa = proj * va;
            mvmath::vec4 pb = proj * vb;
            mvmath::vec4 pc = proj * vc;

            // TODO: Clipping next

            mvmath::vec3 a = (vp * pa.homog_div()).to_vec3();
            mvmath::vec3 b = (vp * pb.homog_div()).to_vec3();
            mvmath::vec3 c = (vp * pc.homog_div()).to_vec3();

            draw_triangle(
                a, b, c,
                (is_color_rand) ? get_rand_col() : tri_col
            );
        }
    }
}