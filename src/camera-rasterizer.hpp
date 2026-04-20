#pragma once
#include "transform.hpp"
#include "render.hpp"
#include "mvmath.hpp"

namespace vkr {

    struct Camera {
    private:
        bool has_changed_m = true;    // Model
                                      // Not necessary for View, as that comes from transform
        bool has_changed_vp = true;   // Viewport
        bool has_changed_proj = true; // Projection matrix

        // Window screen size
        int sc_width;
        int sc_height;
        
        // Projection frame coordinates
        float r_frame = 1, l_frame = -1;
        float t_frame = 1, b_frame = -1;

        float near_plane; // Depth value (z-value) of closest viewable object
        float far_plane;  // Depth value (z-value) of furthest viewable object
        
        // ? Will store the model mat to make it to pre-compute mvp since we only have one model for now
        mvmath::mat4 model = mvmath::mat4::id(); // Model transformation
        mvmath::mat4 view  = mvmath::mat4::id(); // View/Camera transformation
        mvmath::mat4 proj  = mvmath::mat4::id(); // Projection transformation
        mvmath::mat4 vport = mvmath::mat4::id(); // Clip space to Viewport transformation

        mvmath::mat4 modelview = mvmath::mat4::id(); // ModelView precomputed together

    public:
        constexpr static float STD_NEAR_PLANE = 0.05;
        constexpr static float STD_FAR_PLANE = 10;
        constexpr static mvmath::vec3 STD_POS = {0, 0, 1.5};
        constexpr static mvmath::vec3 STD_TARGET = {0, 0, 0};
    
        Transform transform;

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
            has_changed_vp = true;
            sc_width = width;
            sc_height = height;
        }

        constexpr int screen_height() const {
            return sc_height;
        }

        constexpr int screen_width() const {
            return sc_width;
        }

        constexpr void set_model(mvmath::mat4 m) {
            has_changed_m = true;
            model = m;
        }

        constexpr void set_proj_frame(float r, float l, float t, float b) {
            has_changed_proj = true;
            r_frame = r;
            l_frame = l;
            t_frame = t;
            b_frame = b;
        }

        using WinCoord = mvmath::mat4::WinCoord;
        constexpr WinCoord proj_frame() const {
            mvmath::vec2 bl(l_frame, b_frame);
            mvmath::vec2 tr(r_frame, t_frame);
            return {bl, tr};
        }

        constexpr void set_nf_planes(float near_plane, float far_plane) {
            has_changed_proj = true;
            this->near_plane = near_plane; 
            this->far_plane = far_plane; 
        }

        constexpr std::tuple<float, float> nf_planes() const {
            return {near_plane, far_plane};
        }
        
        // Update the matrices before making the mvp/viewport matrix
        void update_mv();
        void update_proj();
        void update_vp();

        // From model to clip space (not-clipped)
        mvmath::mat4 project();

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
        : Camera(pos, sc_width, sc_height, near_plane, far_plane) { }

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
        ) : Camera(pos, sc_width, sc_height, near_plane, far_plane) {
            set_fov(fov_x, static_cast<float>(sc_width) / sc_height);
        }

        // ! Horizontal fov in degrees
        // ! Requires the frame to be symmetrical horizontally (r = -l)
        float fov() const;

        // ! Horizontal fov in degrees
        // ! Alters projection frame coordinates (rltb)
        // ! If aspect ratio (ac) != screen_width() / screen_height(), image will be stretched
        // ! Makes the frame to symmetrical horizontally (r = -l) and vertically (t = -b)
        void set_fov(float fov, float ac);

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

        void render_no_mat(); // Initial render using no matrices, hardcoded transformations and projection
        void render() override;

    };

}