#pragma once
#include "render.hpp"
#include "mvmath.hpp"

namespace vkr {

    struct Camera {
        constexpr static mvmath::vec3 STD_POS = {0, 0, -2};
        constexpr static mvmath::vec3 STD_TARGET = {0, 0, 0};

        enum class Type { ORTHO, PERSP };

        mvmath::vec3 pos;
        mvmath::vec3 target;
        mvmath::vec3 up = {0, 1, 0}; // Normalized vector

        mvmath::mat4 model    = mvmath::mat4::id(); // Model transformations
        mvmath::mat4 view     = mvmath::mat4::id(); // Lookat
        mvmath::mat4 persp    = mvmath::mat4::id(); // Perspective transformation
        mvmath::mat4 viewport = mvmath::mat4::id(); // Project to viewport

        Camera(mvmath::vec3 pos, mvmath::vec3 target, Type type = Type::PERSP)
        : pos(pos), target(target) {
            if(type == Type::PERSP) {
                // TODO
            }
        }
        
        // Update the matrices before projecting
        void update();
        mvmath::vec3 project(mvmath::vec3 v);
    };
    
    struct CameraRasterizer : public IRenderer {
        constexpr static float FRAME_PERCENTAGE = 7./8.;
        
        Camera cam;
        bool is_color_rand = true;
        Color tri_col{};

        CameraRasterizer(
            IFrameBuffer& fb,
            Model& model,
            Camera cam,
            bool is_color_rand = true,
            Color tri_col = {}
        ) : IRenderer(fb, model), cam(cam), is_color_rand(is_color_rand), tri_col(tri_col) {}

        // Uses z-buffer
        void draw_triangle(
            mvmath::vec3 a,
            mvmath::vec3 b,
            mvmath::vec3 c,
            Color col
        );

        void render() override;

    };

}