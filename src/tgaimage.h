#pragma once // Works like the include guard
#include <cstdint>
#include <fstream>
#include <vector>
#include "render.hpp"

namespace vkr {
    namespace tga {
        
        // Adaptation from tinyrenderer by ssloy
        // Changes the padding for the struct alignment.
        // This is used to make sure that header fits into the normal TGA header format.
        // pack(push, 1) makes it so there's no padding between different data types
        //               in a struct
        // pack(push, 2) would add a max of one padding after and every data type would
        //               need to either have pair bytes of allocated bytes or have padding
        //               and so on
        #pragma pack(push,1)
        struct TGAHeader {
            std::uint8_t  idlength = 0;         // Length of imagedescriptor(in bits)
            std::uint8_t  colormaptype = 0;     // 1 if colormap is included/used in this data type 
            std::uint8_t  datatypecode = 0;     // Compression, encoding and image type descriptor
                                                // We will be using run-length-encoding
            std::uint16_t colormaporigin = 0;   // Index of the first used colour map entry (colour)
            std::uint16_t colormaplength = 0;   // Count of colour map entries (colours in palette)
            std::uint8_t  colormapdepth = 0;    // Bits in each colour map entry (colour)
            std::uint16_t x_origin = 0;         // X coord of lower-left corner
            std::uint16_t y_origin = 0;         // Y coord of lower-left corner
            std::uint16_t width = 0;
            std::uint16_t height = 0;
            std::uint8_t  bitsperpixel = 0;     // Bit sizes for BW, RGB, RGBA, etc
            std::uint8_t  imagedescriptor = 0;  // Flags for image encoding and other descriptors
        };
        #pragma pack(pop)
        
        struct TGAColor {
            std::uint8_t bgra[4] = {0,0,0,0};
            std::uint8_t bytespp = 4;  // Bytes per pixel
            constexpr TGAColor() = default;
            constexpr TGAColor(Color c) : bgra{c.b, c.g, c.r, c.a}, bytespp(4) {}
            constexpr TGAColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
                : bgra(b, g, r, a), bytespp(4) {}
            constexpr TGAColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a, std::uint8_t bpp)
                : bgra(b, g, r, a), bytespp(bpp) {}
            std::uint8_t& operator[](const int i) { return bgra[i]; }
            Color to_color() { return { bgra[2], bgra[1], bgra[0], bgra[3]}; }
        };
        
        struct TGAImage: public IFrameBuffer {
            enum Format { GRAYSCALE=1, RGB=3, RGBA=4 };
            std::uint8_t bpp = 0; // Bytes per pixel
            std::vector<std::uint8_t> data = {};
            std::vector<float> depth = {};
            TGAImage() = default;
            TGAImage(const int w, const int h, const int bpp);
            bool  read_tga_file(const std::string filename);
            bool write_tga_file(const std::string filename, const bool vflip=true, const bool rle=true) const;
            void flip_horizontally();
            void flip_vertically();
            Color get(const int x, const int y) const override;
            float get_z(const int x, const int y) const override;
            void set(const int x, const int y, const Color &c) override;
            void set(const int x, const int y, const TGAColor &c);
            void set(const int x, const int y, const float z, const Color &c) override;
            void clear() override;
        private:
            bool   load_rle_data(std::ifstream &in);
            bool unload_rle_data(std::ofstream &out) const;
        };
    
        const std::string DEF_FILENAME = "vkr_out.tga";
    
        struct TGATarget: public IRenderTarget {
            TGAImage fb;
            std::string filename = DEF_FILENAME;
    
            TGATarget() = default;
            TGATarget(int w, int h, int bpp, std::string filename = DEF_FILENAME)
                : fb(w, h, bpp), filename(filename) {}
    
            IFrameBuffer& framebuffer() override { return fb; }
            void present() override;
        };
        
    }
}
