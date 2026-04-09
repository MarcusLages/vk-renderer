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
        has_model_changed = false;
    }

    void Camera::update_vp() {
        // TODO
    }

    mvmath::mat4 Camera::project() {
        if(transform.changed() || has_model_changed) update_mv();
        return proj_mat() * modelview;
    }

    mvmath::mat4 Camera::viewport() {
        // TODO
    }
    
    mvmath::mat4 OrthoCamera::proj_mat() {
        return mvmath::mat4::ortho_project(
            near_plane, far_plane, l_frame, r_frame, b_frame, t_frame
        );
    }

    mvmath::mat4 PerspCamera::proj_mat() {
        return mvmath::mat4::persp_project(
            near_plane, far_plane, l_frame, r_frame, b_frame, t_frame
        );
    }

}