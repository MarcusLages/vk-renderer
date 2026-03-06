#pragma once
#include "mvmath.hpp"

namespace vkr {

    inline void ysort(
        mvmath::vec2& a,
        mvmath::vec2& b,
        mvmath::vec2& c
    ) {
        if(a.y > b.y) std::swap(a, b);
        if(a.y > c.y) std::swap(a, c);
        if(b.y > c.y) std::swap(b, c);
    }
    
} // namespace vkr
