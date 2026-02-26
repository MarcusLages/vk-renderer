#pragma once
#include <cstdint>
#include <vector>

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
constexpr Color white   = {255, 255, 255, 255};
constexpr Color green   = {  0, 255,   0, 255};
constexpr Color red     = {255,   0,   0, 255};
constexpr Color blue    = { 64, 128, 255, 255};
constexpr Color yellow  = {255, 200,   0, 255};

constexpr int DEF_WIDTH = 100;
constexpr int DEF_HEIGHT = 60;

struct IFrameBuffer {
protected:
    int w = DEF_WIDTH;
    int h = DEF_HEIGHT;

public:
    constexpr IFrameBuffer() = default;
    constexpr IFrameBuffer(const int w, const int h): w(w), h(h) {}

    virtual Color get(const int x, const int y) const = 0;
    virtual void set(const int x, const int y, const Color &c) = 0;
    virtual void clear() = 0;

    constexpr int width() const { return w; }
    constexpr int height() const { return h; }
};