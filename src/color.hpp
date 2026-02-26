#pragma once
#include <cstdint>

namespace vkr {

    struct Color {
        // Access color fragments by name or array (bgra order)
        union {
            std::uint8_t rgba[4] = {0, 0, 0, 0};
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
    };
    
    // Common colors
    constexpr Color WHITE   = {255, 255, 255, 255};
    constexpr Color GREEN   = {  0, 255,   0, 255};
    constexpr Color RED     = {255,   0,   0, 255};
    constexpr Color BLUE    = { 64, 128, 255, 255};
    constexpr Color YELLOW  = {255, 200,   0, 255};

}