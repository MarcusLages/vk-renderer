#include "transform.hpp"

namespace vkr {
    
    void Transform::update() {
        mvmath::mat4 scal = mvmath::mat4::scaling(scaling);
        mvmath::mat4 transl = mvmath::mat4::translate(position);
        mvmath::mat4 rot = rotation.mat();
        
        world = transl * rot * scal;
        has_changed = false;
    }

    mvmath::mat4 Transform::inv_model_mat() {
        // Inverse of scaling is their reciprocals
        mvmath::mat4 inv_s = mvmath::mat4::scaling({
            scaling.x == 0 ? scaling.x : 1 / scaling.x,
            scaling.y == 0 ? scaling.y : 1 / scaling.y,
            scaling.z == 0 ? scaling.z : 1 / scaling.z,
        });
        mvmath::mat4 inv_t = mvmath::mat4::translate({
            -position.x,
            -position.y,
            -position.z
        });
        mvmath::mat4 inv_r = rotation.mat().transpose();

        return inv_s * inv_r * inv_t;
    }

}