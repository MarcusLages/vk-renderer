#pragma once
#include "unreachable.hpp"
#include "mvmath.hpp"

namespace vkr {
    
    struct Vertex {
        // TODO: it will have more stuff in it
        mvmath::vec4 clip;

        constexpr Vertex() = default;
        constexpr Vertex(mvmath::vec4 v) : clip(v) {}
        
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
