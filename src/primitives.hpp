#pragma once
#include "mvmath.hpp"

namespace vkr {
    
    struct Vertex {
        // TODO: it will have more stuff in it
        mvmath::vec3 v;

        constexpr Vertex(mvmath::vec3 v) : v(v) {}
    };

    struct Triangle {
        constexpr static int VERT_NUM = 3;

        union {
            Vertex vert[VERT_NUM];
            struct {
                Vertex a;
                Vertex b;
                Vertex c;
            };
        };

        constexpr Triangle(Vertex a, Vertex b, Vertex c) : a(a), b(b), c(c) {}
        constexpr Triangle(mvmath::vec3 a, mvmath::vec3 b, mvmath::vec3 c) 
            : a(a), b(b), c(c) {}
        

        constexpr Vertex& operator[](int i) { return vert[i]; }
        constexpr const Vertex& operator[](int i) const { return vert[i]; }
    };

} // namespace vkr
