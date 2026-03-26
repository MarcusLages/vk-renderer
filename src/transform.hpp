#include "mvmath.hpp"

namespace vkr {

    struct Transform {
    private:
        bool has_changed = false;

        mvmath::vec3 scaling = mvmath::vec3::one();
        mvmath::vec3 position = mvmath::vec3();
        
        // TODO: prob use quaternions later
        // ! Rotation is done on the order XYZ as pivots
        // ! Stores radians
        mvmath::vec3 euler_rot = mvmath::vec3();
        
        // TODO: maybe add shearing

    public:
        static constexpr mvmath::vec3 STD_FORWARD = {0, 0, 1};
        static constexpr mvmath::vec3 STD_UP = {0, 1, 0};

        mvmath::mat4 local = mvmath::mat4::id(); // Local space matrix
        // TODO: have parent pointer and make world matrix using parent
        
        constexpr Transform() = default;

        constexpr void rotate(mvmath::vec3 euler_ang) {
            has_changed = true;
            euler_rot = euler_ang;
        }

        constexpr void scale(float ratio) {
            has_changed = true;
            scaling = mvmath::vec3(ratio);
        }

        constexpr void scale(mvmath::vec3 ratio_vec) {
            has_changed = true;
            scaling = ratio_vec;    
        }

        constexpr mvmath::vec3 local_up() const {
            return STD_UP;
        }

        constexpr mvmath::vec3 local_fwd() const {
            return STD_FORWARD;
        }

        mvmath::vec3 Transform::world_up() {
            if(has_changed) {
                update();
                has_changed = false;
            }
            return local.col(mvmath::mat4::Y_COL).to_vec3(); // Returns y-axis
        }

        mvmath::vec3 Transform::world_fwd() {
            if(has_changed) {
                update();
                has_changed = false;
            }
            return local.col(mvmath::mat4::Z_COL).to_vec3(); // Returns z-axis
        }

        constexpr mvmath::vec3 euler_rot_vec() const {
            return euler_rot;
        }

        constexpr mvmath::vec3 scale_vec() const {
            return scaling;
        }

        constexpr mvmath::vec3 position_vec() const {
            return position;
        }

        constexpr mvmath::mat4 local_mat() {
            if(has_changed) {
                update();
                has_changed = false;
            }
            return local;
        }

        virtual void update() = 0;
    };
    
} // namespace vkr
