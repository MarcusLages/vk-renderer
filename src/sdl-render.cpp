#include <stdexcept>
#include "sdl-render.hpp"

namespace vkr {
    namespace sdl {

        SDLFrameBuffer::~SDLFrameBuffer() {
            if(win) SDL_DestroyWindow(win);
            win = nullptr;
            surf = nullptr;
        }

        //! Returns transparent black (Color{}) if out of bounds
        Color SDLFrameBuffer::get(const int x, const int y) const {
            if (x < 0 || y < 0 || x >= w || y >= h) return {};

            const int real_y = h - y - 1;
            std::uint32_t* pixel_frame = static_cast<uint32_t*>(surf->pixels);
            std::uint32_t pixel = pixel_frame[real_y * surf->w + x];
            
            Color c;
            SDL_GetRGBA(pixel, surf->format, &(c.r), &(c.g), &(c.b), &(c.a));
            return c;
        }
        
        void SDLFrameBuffer::set(const int x, const int y, const Color &c) {
            if (x < 0 || y < 0 || x >= w || y >= h) return;

            const int real_y = h - y - 1;
            std::uint32_t* pixel_frame = static_cast<uint32_t*>(surf->pixels);
            std::uint32_t pixel = SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a);
            pixel_frame[real_y * surf->w + x] = pixel;
        }

        void SDLFrameBuffer::clear() {
            // 0x0 is uint32_t representing rgba(0, 0, 0, 0)
            SDL_FillRect(surf, nullptr, 0x0);
        }

        SDLTarget::SDLTarget(int w, int h, std::string win_name)
        : fb(w, h, win_name) {
            if(SDL_Init(SDL_INIT_VIDEO))
                throw std::runtime_error("SDL wasn't able to be initiallized.");
                
            fb.win = SDL_CreateWindow(
                fb.win_name.data(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                fb.width(),
                fb.height(),
                SDL_WINDOW_SHOWN
            );
            if(!fb.win) {
                SDL_Quit();
                throw std::runtime_error("SDL wasn't able to create a window.");
            }
            
            fb.surf = SDL_GetWindowSurface(fb.win);
            if(!fb.surf) {
                SDL_DestroyWindow(fb.win);
                SDL_Quit();
                throw std::runtime_error("SDL wasn't able to create a window.");
            }
        }

        SDLTarget::~SDLTarget() {
            fb = nullptr;
            SDL_Quit();
        }
        
        void SDLTarget::present() {
            // TODO: Rendering loop is temporary
            bool quit = false;
            SDL_Event e;
            while(!quit) {
                SDL_UpdateWindowSurface(fb.win);
                while(SDL_PollEvent(&e))
                    if(e.type == SDL_QUIT)
                        quit = true;
            }
        }

    }
}