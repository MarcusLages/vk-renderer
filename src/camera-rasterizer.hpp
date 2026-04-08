#pragma once
#include "transform.hpp"
#include "render.hpp"
#include "mvmath.hpp"

namespace vkr {

    struct Camera {
    private:
        bool has_changed_mv = false; // ModelView
        bool has_changed_vp = false; // Viewport

        // ? Will store the model mat to make it to pre-compute mvp since we only have one model for now
        mvmath::mat4 model = mvmath::mat4::id(); // Model transformation
        mvmath::mat4 view  = mvmath::mat4::id(); // View/Camera transformation
        mvmath::mat4 vport = mvmath::mat4::id(); // Clip space to Viewport transformation

        mvmath::mat4 mv_cache = mvmath::mat4::id(); // Model-View

    public:
        constexpr static mvmath::vec3 STD_POS = {0, 0, -2};
        constexpr static mvmath::vec3 STD_TARGET = {0, 0, 0};
    
        Transform transform;

        Camera(mvmath::vec3 pos, mvmath::vec3 target = STD_TARGET) {
            // Order matters
            transform.translate(pos);
            transform.look_at(STD_TARGET);
        }

        constexpr void set_model(mvmath::mat4 m) {
            has_changed_mv = true;
            model = m;
        }
        
        // Update the matrices before making the mvp/viewport matrix
        void update_mv();
        void update_vp();

        // From model to clip space (not-clipped)
        mvmath::mat4 project(mvmath::vec3 v);

        // From clip space (should be clipped) to window space
        mvmath::mat4 viewport();

    protected:
        virtual mvmath::mat4 proj_mat() = 0;

    private:
        mvmath::mat4 view_mat();
        mvmath::mat4 vport_mat();

    };

    struct PerspCamera : Camera {
        mvmath::mat4 proj_mat() override {}
    };

    struct OrthoCamera : Camera {
        mvmath::mat4 proj_mat() override {}
    };
    
    struct CameraRasterizer : public IRenderer {
        constexpr static float FRAME_PERCENTAGE = 3./4.;
        
        Camera& cam;
        bool is_color_rand = true;
        Color tri_col{};

        CameraRasterizer(
            IFrameBuffer& fb,
            Model& model,
            Camera& cam,
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