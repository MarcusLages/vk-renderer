#pragma once
#include "color.hpp"

namespace vkr {

    constexpr int DEF_FRAME_WIDTH = 100;
    constexpr int DEF_FRAME_HEIGHT = 60;
    
    struct IFrameBuffer {
    protected:
        int w = DEF_FRAME_WIDTH;
        int h = DEF_FRAME_HEIGHT;
    
    public:
        IFrameBuffer() = default;
        IFrameBuffer(const int w, const int h): w(w), h(h) {}
        virtual ~IFrameBuffer() = default;
    
        virtual Color get(const int x, const int y) const = 0;
        virtual void set(const int x, const int y, const Color &c) = 0;
        virtual void clear() = 0;
    
        constexpr int width() const { return w; }
        constexpr int height() const { return h; }
    };
    
    struct IRenderTarget {
        virtual ~IRenderTarget() = default;
        virtual IFrameBuffer& framebuffer() = 0;
        virtual void present() = 0;
    };

}