#pragma once
#include "mvmath.hpp"

// Just used for a safer compilation
#if defined(__cpp_lib_unreachable) && (__cpp_lib_unreachable >= 202202L)
    #define _UNREACHABLE() std::unreachable()
#elif defined(_MSC_VER)
    #define _UNREACHABLE() __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
    #define _UNREACHABLE() __builtin_unreachable()
#else
    #define _UNREACHABLE() abort()
#endif


namespace vkr {
    
    struct Vertex {
        // TODO: it will have more stuff in it
        mvmath::vec4 clip;

        constexpr Vertex() = default;
        constexpr Vertex(mvmath::vec4 v) : clip(v) {}

        // Degenerate division by 0 on z-division
        inline const bool is_valid() const {
            return !mvmath::is_equalf(clip.w, 0);
        }
    };

    struct Triangle {
        constexpr static int VERT_NUM = 3;

        enum Idx {
            A = 0,
            B = 1,
            C = 2
        };

        Vertex a, b, c;

        // ! Degenerate triangle
        constexpr Triangle() = default;

        // ! Counter-clockwise order
        constexpr Triangle(Vertex a, Vertex b, Vertex c) : a(a), b(b), c(c) {}
        
        // ! Counter-clockwise order
        constexpr Triangle(mvmath::vec3 a, mvmath::vec3 b, mvmath::vec3 c) 
            : a(a), b(b), c(c) {}

        constexpr Vertex& operator[](int i) {
            switch(i) {
                case Idx::A: return a;
                case Idx::B: return b;
                case Idx::C: return c;
                default: _UNREACHABLE();
            }
        }

        constexpr const Vertex& operator[](int i) const {
            switch(i) {
                case Idx::A: return a;
                case Idx::B: return b;
                case Idx::C: return c;
                default: _UNREACHABLE();
            }
        }

        // Used to check if all w != 0 to not cause 0 division
        inline const bool is_valid() const {
            return a.is_valid() && b.is_valid() && c.is_valid();
        }

        constexpr void apply_mat_clip(mvmath::mat4 transf) {
            a.clip = transf * a.clip;
            b.clip = transf * b.clip;
            c.clip = transf * c.clip;
        }

        constexpr void homog_div_clip() {
            a.clip = a.clip.homog_div();
            b.clip = b.clip.homog_div();
            c.clip = c.clip.homog_div();
        }
    };

} // namespace vkr
