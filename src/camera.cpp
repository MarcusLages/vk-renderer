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
        mv_cache = view * model;
        has_changed_mv = false;
    }

    void Camera::update_vp() {
        // TODO
    }

    mvmath::mat4 Camera::project(mvmath::vec3 v) {
        if(transform.changed() || has_changed_mv) update_mv();
        // TODO
    }

    mvmath::mat4 Camera::viewport() {
        // TODO
    }

    mvmath::mat4 PerspCamera::proj_mat() {
        // TODO
    }

    mvmath::mat4 OrthoCamera::proj_mat() {
        // TODO
    }

}