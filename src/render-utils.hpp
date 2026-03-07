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
        // I have no idea how to name this constant, but either way, you understood it
        constexpr int UINT8_OVERLOAD = Color::MAX_COLOR_CHANNEL + 1;
        return {
            static_cast<uint8_t>(std::rand() % UINT8_OVERLOAD), // Pseudo random since I didn't set a seed
            static_cast<uint8_t>(std::rand() % UINT8_OVERLOAD),
            static_cast<uint8_t>(std::rand() % UINT8_OVERLOAD),
            Color::MAX_COLOR_CHANNEL
        };
    }
    
} // namespace vkr
