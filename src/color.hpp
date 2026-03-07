#pragma once
#include <cstdint>

namespace vkr {

    struct Color {
        static constexpr std::uint8_t MAX_COLOR_CHANNEL = 0xFF;

        union {
            std::uint8_t rgba[4] = {0, 0, 0, 0}; // Transparent black
            struct {
                std::uint8_t r;
                std::uint8_t g;
                std::uint8_t b;
                std::uint8_t a;
            };
        };
    
        //? Explicit because of compiler warnings with union types
        constexpr Color() = default;
        constexpr Color(std::uint8_t r,
                        std::uint8_t g,
                        std::uint8_t b,
                        std::uint8_t a)
            : rgba{r, g, b, a} {}
        
        constexpr std::uint8_t& operator[](int i) {
            return rgba[i];
        }
        
        constexpr const std::uint8_t& operator[](int i) const {
            return rgba[i];
        }

        constexpr bool operator==(Color c) const {
            return r == c.r &&
                   g == c.g &&
                   b == c.b &&
                   a == c.a;
        }
    };
    
    // Common colors
    constexpr Color COL_BLACK   = {  0,   0,   0, 255};
    constexpr Color COL_WHITE   = {255, 255, 255, 255};
    constexpr Color COL_GREEN   = {  0, 255,   0, 255};
    constexpr Color COL_RED     = {255,   0,   0, 255};
    constexpr Color COL_BLUE    = { 64, 128, 255, 255};
    constexpr Color COL_YELLOW  = {255, 200,   0, 255};

}