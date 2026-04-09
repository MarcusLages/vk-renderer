#pragma once
#include "transform.hpp"
#include "render.hpp"
#include "mvmath.hpp"

namespace vkr {

    struct Camera {
    private:
        bool has_model_changed = true; // ModelView
        bool has_changed_vp = true;    // Viewport

        int sc_width;
        int sc_height; 
        
        // ? Will store the model mat to make it to pre-compute mvp since we only have one model for now
        mvmath::mat4 model = mvmath::mat4::id(); // Model transformation
        mvmath::mat4 view  = mvmath::mat4::id(); // View/Camera transformation
        mvmath::mat4 vport = mvmath::mat4::id(); // Clip space to Viewport transformation

        mvmath::mat4 modelview = mvmath::mat4::id(); // ModelView precomputed together

    public:
        constexpr static float STD_NEAR_PLANE = 0.05;
        constexpr static float STD_FAR_PLANE = 10;
        constexpr static mvmath::vec3 STD_POS = {0, 0, -2};
        constexpr static mvmath::vec3 STD_TARGET = {0, 0, 0};
    
        Transform transform;

        // Projection frame coordinates
        float r_frame = 1, l_frame = -1;
        float t_frame = 1, b_frame = -1;

        float near_plane; // Depth value (z-value) of closest viewable object
        float far_plane;  // Depth value (z-value) of furthest viewable object

        Camera(
            mvmath::vec3 pos, 
            int sc_width, 
            int sc_height,
            float near_plane = STD_NEAR_PLANE,
            float far_plane = STD_FAR_PLANE)
        : sc_width(sc_width), 
          sc_height(sc_height),
          near_plane(near_plane),
          far_plane(far_plane) {

            // Initialize camera looking from -2 to 0 depth
            transform.translate(pos);
            transform.look_at(STD_TARGET);
        }

        constexpr void set_screen_info(int width, int height) {
            sc_width = width;
            sc_height = height;
            has_changed_vp = true;
        }

        // Returns std::tuple{w, h}
        constexpr std::tuple<int, int> screen_info() const {
            return {sc_width, sc_height};
        }

        constexpr void set_model(mvmath::mat4 m) {
            has_model_changed = true;
            model = m;
        }
        
        // Update the matrices before making the mvp/viewport matrix
        void update_mv();
        void update_vp();

        // From model to clip space (not-clipped)
        // Use pre-computation on project too
        mvmath::mat4 project(); // Default projection symmetric on origin

        // From clip space (should be clipped) to window space
        mvmath::mat4 viewport();

    protected:
        virtual mvmath::mat4 proj_mat() = 0;

    private:
        mvmath::mat4 view_mat();
        mvmath::mat4 vport_mat();

    };

    struct OrthoCamera : Camera {
        OrthoCamera(
            mvmath::vec3 pos, 
            int sc_width, 
            int sc_height,
            float near_plane = STD_NEAR_PLANE,
            float far_plane = STD_FAR_PLANE)
        : Camera(sc_width, sc_height, near_plane, far_plane) { }

        mvmath::mat4 proj_mat() override;
    };

    struct PerspCamera : Camera {
        constexpr static float STD_FOV_X = 90; // Degrees

        PerspCamera(
            mvmath::vec3 pos, 
            int sc_width, 
            int sc_height,
            float fov_x = STD_FOV_X,
            float near_plane = STD_NEAR_PLANE,
            float far_plane = STD_FAR_PLANE
        ) : Camera(sc_width, sc_height, near_plane, far_plane) {
            auto [bl, tr] = mvmath::mat4::frame_from_fov(
                fov_x, sc_width / sc_height, near_plane
            );
            r_frame = tr.x;
            l_frame = bl.x;
            t_frame = tr.y;
            b_frame = bl.y;
        }

        float get_fov();

        // ! Horizontal fov in degrees
        // ! Alters projection frame coordinates (rltb)
        void set_fov(float fov);

        mvmath::mat4 proj_mat() override;
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