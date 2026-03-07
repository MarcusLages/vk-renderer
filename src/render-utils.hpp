#pragma once
#include <cstdlib>
#include "color.hpp"
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

    inline Color get_rand_col() {
        return {
            static_cast<uint8_t>(std::rand() % 256), // Pseudo random since I didn't set a seed
            static_cast<uint8_t>(std::rand() % 256),
            static_cast<uint8_t>(std::rand() % 256),
            255
        };
    }
    
} // namespace vkr
