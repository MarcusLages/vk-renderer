#pragma once
#include "mvmath.hpp"

namespace vkr {

    // Will use this before using quaternions
    // TODO: Apply quaternions
    struct Rotation {
        enum class Type { EULER, LOOK_AT };

        // ! Euler rotation is done on the order XYZ as pivots
        //   Euler rotation stores angles as rad
        struct Euler {
            mvmath::vec3 rad = mvmath::vec3();
        };

        struct LookAt {
            mvmath::vec3 to;
            mvmath::vec3 up;
            mvmath::mat4 prev_rot = mvmath::mat4::id();
        };

    private:
        constexpr Rotation() = delete;
        constexpr Rotation(Euler eu_rad)
            : t(Type::EULER), euler(eu_rad) {}
        constexpr Rotation(LookAt look)
            : t(Type::LOOK_AT), look(look) {}

    public:
        Type t;

        union {
            Euler euler;
            LookAt look;
        };

        static constexpr Rotation from_euler(mvmath::vec3 euler_rad) {
            return Rotation(Euler(euler_rad));
        }

        // ! Assumes "to" vector to be a deslocation from vec3::zero()
        static constexpr Rotation from_look_at(
            mvmath::vec3 to,
            mvmath::vec3 up,
            mvmath::mat4 prev_rot = mvmath::mat4::id()
        ) {
            return Rotation(
                LookAt(to, up, prev_rot)
            );
        }

        static constexpr Rotation zero() {
            return Rotation::from_euler(mvmath::vec3());
        }

        mvmath::mat4 mat() {
            switch(t) {
            case Type::EULER:
                return mvmath::mat4::rotate(euler.rad);
            case Type::LOOK_AT:
                return mvmath::mat4::look_at(
                    mvmath::vec3_ZERO,
                    look.to,
                    look.up,
                    look.prev_rot
                );
            default:
                return mvmath::mat4_ID;
            }
        }
    };

    inline constexpr Rotation rotation_ZERO = Rotation::zero();

    struct Transform {
    private:
        bool has_changed = false;

        mvmath::vec3 scaling = mvmath::vec3::one();
        mvmath::vec3 position = mvmath::vec3();
        Rotation rotation = Rotation::zero();
        // TODO: maybe add shearing

    public:
        static constexpr mvmath::vec3 STD_FORWARD = {0, 0, 1};
        static constexpr mvmath::vec3 STD_UP = {0, 1, 0};

        mvmath::mat4 world = mvmath::mat4::id(); // Local space matrix
        // TODO: have parent pointer and make world matrix using parent
        
        constexpr Transform() = default;

        constexpr void translate(mvmath::vec3 pos) {
            has_changed = true;
            position = pos;
        }

        constexpr void rotate(mvmath::vec3 euler_rad) {
            has_changed = true;
            rotation = Rotation::from_euler(euler_rad);
        }

        constexpr void look_at(mvmath::vec3 to) {
            has_changed = true;
            rotation = Rotation::from_look_at(to - position, STD_UP);
        }

        constexpr void scale(float ratio) {
            has_changed = true;
            scaling = mvmath::vec3(ratio);
        }

        constexpr void scale(mvmath::vec3 ratio_vec) {
            has_changed = true;
            scaling = ratio_vec;    
        }

        constexpr mvmath::vec3 local_up() const { return STD_UP; }

        constexpr mvmath::vec3 local_fwd() const { return STD_FORWARD; }

        inline mvmath::vec3 world_up() {
            if(has_changed) update();
            return world.col(mvmath::mat4::Y_COL).to_vec3(); // Returns y-axis
        }

        inline mvmath::vec3 world_fwd() {
            if(has_changed) update();
            return world.col(mvmath::mat4::Z_COL).to_vec3(); // Returns z-axis
        }

        constexpr bool changed() const { return has_changed; }
        
        constexpr mvmath::vec3 scale_vec() const { return scaling; }
        
        constexpr mvmath::vec3 position_vec() const { return position; }
        
        constexpr Rotation rotation_val() const { return rotation; }

        // Model to world matrix
        inline mvmath::mat4 model_mat() {
            if(has_changed) update();
            return world;
        }

        // World to model matrix
        mvmath::mat4 inv_model_mat();
        void update();
    };
    
} // namespace vkr
