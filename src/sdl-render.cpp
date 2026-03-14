#include <stdexcept>
#include "sdl-render.hpp"

namespace vkr {
    namespace sdl {
        
        SDLFrameBuffer::~SDLFrameBuffer() {
            // Considers that the window closes the Surface
            // Just here to notify that
            surf = nullptr;
        }

        void SDLFrameBuffer::init(SDL_Surface* surf) {
            this->surf = surf;
            h = surf->h;
            w = surf->w;

            buffer.assign(surf->h * surf->w, Color{});
            depth.assign(surf->h * surf->w, std::numeric_limits<float>::max());
        }

        void SDLFrameBuffer::update_surface() {
            SDL_LockSurface(surf);

            int real_y = 0;
            for(int y = 0; y < h; y++) {
                for(int x = 0; x < w; x++) {
                    // - 1 since it's in range [0, h-1], 
                    // and h - y because the y-axis is flipped in sdl
                    real_y = h - y - 1;

                    Color& c = buffer[y * w + x];
                    std::uint32_t* pixel_frame = static_cast<uint32_t*>(surf->pixels);
                    std::uint32_t pixel = SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a);
                    pixel_frame[real_y * surf->w + x] = pixel;
                }
            }
            
            SDL_UnlockSurface(surf);
        }

        void SDLFrameBuffer::update_surface_zbuf() {
            SDL_LockSurface(surf);

            int real_y = 0;
            for(int y = 0; y < h; y++) {
                for(int x = 0; x < w; x++) {
                    // - 1 since it's in range [0, h-1], 
                    // and h - y because the y-axis is flipped in sdl
                    real_y = h - y - 1;
                    uint8_t intensity = static_cast<uint8_t>(depth[y * w + x] * Color::MAX_COLOR_CHANNEL);
                    Color c = {intensity, intensity, intensity, Color::MAX_COLOR_CHANNEL};

                    std::uint32_t* pixel_frame = static_cast<uint32_t*>(surf->pixels);
                    std::uint32_t pixel = SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a);
                    pixel_frame[real_y * surf->w + x] = pixel;
                }
            }
            
            SDL_UnlockSurface(surf);
        }

        Color SDLFrameBuffer::get(const int x, const int y) const {
            return buffer[y * w + x];
        }

        float SDLFrameBuffer::get_z(const int x, const int y) const {
            return depth[y * w + x];
        }

        // Not the best, use only if doing one-face models and does not need
        // z-buffer/depth-buffer
        void SDLFrameBuffer::set(const int x, const int y, const Color& c) {
            buffer[y * w + x] = c;
        }

        void SDLFrameBuffer::set(const int x, const int y, const float z, const Color& c) {
            buffer[y * w + x] = c;
            depth[y * w + x] = z;
        }

        void SDLFrameBuffer::clear() {
            // ! Default clear color is transparent black or {0, 0, 0, 0}
            std::fill(buffer.begin(), buffer.end(), Color{});
            std::fill(depth.begin(), depth.end(), std::numeric_limits<float>::max());
        }

        SDLTarget::SDLTarget(int w, int h, std::string window_name) 
        : window_name(window_name), fb() {
            if(SDL_Init(SDL_INIT_VIDEO))
                throw std::runtime_error("SDL wasn't able to be initiallized.");
                
            win = SDL_CreateWindow(
                window_name.data(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                w, h,
                SDL_WINDOW_SHOWN
            );
            if(!win) {
                SDL_Quit();
                throw std::runtime_error("SDL wasn't able to create a window.");
            }
            
            SDL_Surface* surf = SDL_GetWindowSurface(win);
            if(!surf) {
                SDL_DestroyWindow(win);
                SDL_Quit();
                throw std::runtime_error("SDL wasn't able to initiallize surface framebuffer.");
            }

            fb.init(surf);
        }

        SDLTarget::~SDLTarget() {
            SDL_DestroyWindow(win);
            SDL_Quit();
        }
        
        void SDLTarget::present() {
            fb.update_surface();
            SDL_UpdateWindowSurface(win);
        }
        
        void SDLTarget::present_depth() {
            fb.update_surface_zbuf();
            SDL_UpdateWindowSurface(win);
        }
        
        // TODO: take this out later when I have a centralized runner
        void SDLTarget::run() {
            bool quit = false;
            SDL_Event e;
            present();
            
            while(!quit) {
                // TODO: update the loop better
                SDL_UpdateWindowSurface(win);
                while(SDL_PollEvent(&e))
                    if(e.type == SDL_QUIT)
                        quit = true;
            }
        }
        // TODO: take this out later when I have a centralized runner
        void SDLTarget::run_depth() {
            bool quit = false;
            SDL_Event e;
            present_depth();
            
            while(!quit) {
                // TODO: update the loop better
                SDL_UpdateWindowSurface(win);
                while(SDL_PollEvent(&e))
                    if(e.type == SDL_QUIT)
                        quit = true;
            }
        }
    }
}