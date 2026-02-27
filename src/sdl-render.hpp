#pragma once
#include <string>
#include <SDL.h>
#include "render.hpp"

namespace vkr {
    namespace sdl {

        const std::string DEF_WINDOW_NAME = "vkr";

        //! Will have to create my own inner framebuffer vector later to make sure concurrency is right
        struct SDLFrameBuffer : public IFrameBuffer {
            std::string win_name = DEF_WINDOW_NAME;
            SDL_Window* win = nullptr;
            SDL_Surface* surf = nullptr;
            

            SDLFrameBuffer(const int w, const int h, std::string win_name = DEF_WINDOW_NAME) 
                : IFrameBuffer(w, h), win_name(win_name) {}
            SDLFrameBuffer(SDL_Window* window, std::string win_name = DEF_WINDOW_NAME)
            : win(window), win_name(win_name) {
                surf = SDL_GetWindowSurface(win);
                w = surf->w;
                h = surf->h;
            }
            ~SDLFrameBuffer();

            
            //! Returns transparent black (Color{}) if out of bounds
            Color get(const int x, const int y) const override;
            void set(const int x, const int y, const Color &c) override;
            void clear() override;
        };
        
        //! Works like an SDL RAII context so only one SDLTarget is allowed
        struct SDLTarget : public IRenderTarget {
            SDLFrameBuffer fb;
    
            SDLTarget(int w, int h, std::string win_name = DEF_WINDOW_NAME);
            ~SDLTarget();
    
            IFrameBuffer& framebuffer() override { return fb; }
            void present() override;
            std::string window_name() { return fb.win_name; }
        };

    }
}