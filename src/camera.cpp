#include "camera-rasterizer.hpp"

namespace vkr {

    mvmath::mat4 Camera::view_mat() {
        mvmath::mat4 world_to_cam = transform.inv_model_mat();

        // Used to rotate the camera to the negative side to maintain right-handedness
        mvmath::mat4 rot_to_neg_z = mvmath::mat4::rotate_y(mvmath::deg_to_rad(180));
        return rot_to_neg_z * world_to_cam;
    }

    mvmath::mat4 Camera::vport_mat() {
        // TODO
    }

    void Camera::update_mv() {
        view = view_mat();
        modelview = view * model;
        has_changed_m = false;
    }

    void Camera::update_proj() {
        proj = proj_mat();
        has_changed_proj = false;
    }

    void Camera::update_vp() {
        // TODO
    }

    mvmath::mat4 Camera::project() {
        if(transform.changed() || has_changed_m) update_mv();
        if(has_changed_proj) update_proj();
        return proj * modelview;
    }

    mvmath::mat4 Camera::viewport() {
        // TODO
    }
    
    mvmath::mat4 OrthoCamera::proj_mat() {
        auto [n, f] = nf_planes();
        auto [bl, tr] = proj_frame();
        return mvmath::mat4::ortho_project(n, f, bl.x, tr.x, bl.y, tr.y);
    }

    float PerspCamera::fov() const {
        auto [_, tr] = proj_frame();
        auto [n, _] = nf_planes();
        return 2 * mvmath::mat4::fov_from_length(tr.x, n); // tr.x is only half
    }

    void PerspCamera::set_fov(float fov, float ac) {
        auto [n, _] = nf_planes();
        auto [bl, tr] = mvmath::mat4::frame_from_fov(fov, ac, n);
        set_proj_frame(tr.x, bl.x, tr.y, bl.y);
    }

    mvmath::mat4 PerspCamera::proj_mat() {
        auto [n, f] = nf_planes();
        auto [bl, tr] = proj_frame();
        return mvmath::mat4::persp_project(n, f, bl.x, tr.x, bl.y, tr.y);
    }

}