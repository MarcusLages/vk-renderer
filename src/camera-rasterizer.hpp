#pragma once
#include "render.hpp"

namespace vkr {
    
    struct CameraRasterizer : public IRenderer {
        constexpr static float FRAME_PERCENTAGE = 7./8.;
        
        bool is_color_rand = true;
        Color tri_col{};

        CameraRasterizer(
            IFrameBuffer& fb,
            Model& model,
            bool is_color_rand = true,
            Color tri_col = {}
        ) : IRenderer(fb, model), is_color_rand(is_color_rand), tri_col(tri_col) {}

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