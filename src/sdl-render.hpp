#pragma once
#include <string>
#include <vector>
#include <limits>
#include <SDL.h>
#include "render.hpp"

namespace vkr {
    namespace sdl {

        const std::string DEF_WINDOW_NAME = "vkr";

        //! Will have to create my own inner framebuffer vector later to make sure concurrency is right
        struct SDLFrameBuffer : public IFrameBuffer {
            std::vector<Color> buffer;
            std::vector<float> depth;
            SDL_Surface* surf = nullptr;

            SDLFrameBuffer() = default; // Avoid, if possible (will have to initiallize all manually)
            SDLFrameBuffer(SDL_Surface* surf)
                : surf(surf), 
                IFrameBuffer(surf->w, surf->h), 
                buffer(surf->w * surf->h), 
                depth(surf->w * surf->h, std::numeric_limits<float>::max()) {}
            ~SDLFrameBuffer();

            // Should be called if the default constructor was used
            void init(SDL_Surface* surf);
            void update_surface();
            
            // TODO: add z-related functions to IFrameBuffers
            //! Returns transparent black (Color{}) if out of bounds
            Color get(const int x, const int y) const override;
            float get_z(const int x, const int y) const;
            void set(const int x, const int y, const Color &c) override;
            void set(const int x, const int y, const float z, const Color &c);
            void clear() override;
        };
        
        //! Works like an SDL RAII context so only one SDLTarget is allowed
        struct SDLTarget : public IRenderTarget {
            std::string window_name;
            SDLFrameBuffer fb;
            SDL_Window* win = nullptr;
    
            SDLTarget(int w, int h, std::string window_name = DEF_WINDOW_NAME);
            ~SDLTarget();
    
            IFrameBuffer& framebuffer() override { return fb; }
            void present() override;
            void run(); // TODO: take this out later when I have a centralized runner
        };

    }
}