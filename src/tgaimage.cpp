#include <iostream>
#include <limits>
#include <cstring>
#include "tgaimage.h"

namespace vkr {
    namespace tga {

        // Adaptation from tinyrenderer by ssloy
        // auto init vector data
        TGAImage::TGAImage(const int w, const int h, const int bpp) 
            : IFrameBuffer(w, h), bpp(bpp), data(w * h * bpp, 0), depth(w * h, std::numeric_limits<float>::max()) {}
    
        bool TGAImage::read_tga_file(const std::string filename) {
            std::ifstream in;
            in.open(filename, std::ios::binary);
            if (!in.is_open()) {
                std::cerr << "can't open file " << filename << "\n";
                return false;
            }
            TGAHeader header;
            in.read(reinterpret_cast<char *>(&header), sizeof(header));
            if (!in.good()) {
                std::cerr << "an error occured while reading the header\n";
                return false;
            }
            w = header.width;
            h = header.height;
            bpp = header.bitsperpixel >> 3;
            depth.assign(w * h, std::numeric_limits<float>::max());
            if (w <= 0 || h <= 0 || (bpp != GRAYSCALE && bpp != RGB && bpp != RGBA)) {
                std::cerr << "bad bpp (or width/height) value\n";
                return false;
            }
            size_t nbytes = bpp * w * h;
            data = std::vector<std::uint8_t>(nbytes, 0);
            if (3 == header.datatypecode || 2 == header.datatypecode) {
                in.read(reinterpret_cast<char *>(data.data()), nbytes);
                if (!in.good()) {
                    std::cerr << "an error occured while reading the data\n";
                    return false;
                }
            }
            else if (10 == header.datatypecode || 11 == header.datatypecode) {
                if (!load_rle_data(in)) {
                    std::cerr << "an error occured while reading the data\n";
                    return false;
                }
            }
            else {
                std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
                return false;
            }
            if (!(header.imagedescriptor & 0x20))
                flip_vertically();
            if (header.imagedescriptor & 0x10)
                flip_horizontally();
            std::cerr << w << "x" << h << "/" << bpp * 8 << "\n";
            return true;
        }
    
        bool TGAImage::load_rle_data(std::ifstream &in) {
            size_t pixelcount = w * h;
            size_t currentpixel = 0;
            size_t currentbyte = 0;
            TGAColor colorbuffer;
            do {
                std::uint8_t chunkheader = 0;
                chunkheader = in.get();
                if (!in.good()) {
                    std::cerr << "an error occured while reading the data\n";
                    return false;
                }
                if (chunkheader < 128) {
                    chunkheader++;
                    for (int i = 0; i < chunkheader; i++)
                    {
                        in.read(reinterpret_cast<char *>(colorbuffer.bgra), bpp);
                        if (!in.good())
                        {
                            std::cerr << "an error occured while reading the header\n";
                            return false;
                        }
                        for (int t = 0; t < bpp; t++)
                            data[currentbyte++] = colorbuffer.bgra[t];
                        currentpixel++;
                        if (currentpixel > pixelcount)
                        {
                            std::cerr << "Too many pixels read\n";
                            return false;
                        }
                    }
                }
                else {
                    chunkheader -= 127;
                    in.read(reinterpret_cast<char *>(colorbuffer.bgra), bpp);
                    if (!in.good())
                    {
                        std::cerr << "an error occured while reading the header\n";
                        return false;
                    }
                    for (int i = 0; i < chunkheader; i++)
                    {
                        for (int t = 0; t < bpp; t++)
                            data[currentbyte++] = colorbuffer.bgra[t];
                        currentpixel++;
                        if (currentpixel > pixelcount)
                        {
                            std::cerr << "Too many pixels read\n";
                            return false;
                        }
                    }
                }
            } while (currentpixel < pixelcount);
            return true;
        }
    
        bool TGAImage::write_tga_file(const std::string filename, const bool vflip, const bool rle) const {
            constexpr std::uint8_t developer_area_ref[4] = {0, 0, 0, 0};
            constexpr std::uint8_t extension_area_ref[4] = {0, 0, 0, 0};
            constexpr std::uint8_t footer[18] = {'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O', 'N', '-', 'X', 'F', 'I', 'L', 'E', '.', '\0'};
            std::ofstream out;
            out.open(filename, std::ios::binary);
            if (!out.is_open()) {
                std::cerr << "can't open file " << filename << "\n";
                return false;
            }
            TGAHeader header = {};
            header.bitsperpixel = bpp << 3;
            header.width = w;
            header.height = h;
            header.datatypecode = (bpp == GRAYSCALE ? (rle ? 11 : 3) : (rle ? 10 : 2));
            header.imagedescriptor = vflip ? 0x00 : 0x20; // top-left or bottom-left origin
            out.write(reinterpret_cast<const char *>(&header), sizeof(header));
            if (!out.good())
                goto err;
            if (!rle) {
                out.write(reinterpret_cast<const char *>(data.data()), w * h * bpp);
                if (!out.good())
                    goto err;
            }
            else if (!unload_rle_data(out))
                goto err;
            out.write(reinterpret_cast<const char *>(developer_area_ref), sizeof(developer_area_ref));
            if (!out.good())
                goto err;
            out.write(reinterpret_cast<const char *>(extension_area_ref), sizeof(extension_area_ref));
            if (!out.good())
                goto err;
            out.write(reinterpret_cast<const char *>(footer), sizeof(footer));
            if (!out.good())
                goto err;
            return true;
        err:
            std::cerr << "can't dump the tga file\n";
            return false;
        }
    
        bool TGAImage::unload_rle_data(std::ofstream &out) const {
            const std::uint8_t max_chunk_length = 128;
            size_t npixels = w * h;
            size_t curpix = 0;
            while (curpix < npixels) {
                size_t chunkstart = curpix * bpp;
                size_t curbyte = curpix * bpp;
                std::uint8_t run_length = 1;
                bool raw = true;
                while (curpix + run_length < npixels && run_length < max_chunk_length) {
                    bool succ_eq = true;
                    for (int t = 0; succ_eq && t < bpp; t++)
                        succ_eq = (data[curbyte + t] == data[curbyte + t + bpp]);
                    curbyte += bpp;
                    if (1 == run_length)
                        raw = !succ_eq;
                    if (raw && succ_eq)
                    {
                        run_length--;
                        break;
                    }
                    if (!raw && !succ_eq)
                        break;
                    run_length++;
                }
                curpix += run_length;
                out.put(raw ? run_length - 1 : run_length + 127);
                if (!out.good())
                    return false;
                out.write(reinterpret_cast<const char *>(data.data() + chunkstart), (raw ? run_length * bpp : bpp));
                if (!out.good())
                    return false;
            }
            return true;
        }
    
        Color TGAImage::get(const int x, const int y) const {
            TGAColor ret = {0, 0, 0, 0, bpp};
            const std::uint8_t *p = data.data() + (x + y * w) * bpp;
            for (int i = bpp; i--; ret.bgra[i] = p[i]);
            return ret.to_color();
        }

        float TGAImage::get_z(const int x, const int y) const {
            return depth[y * w + x];
        }
    
        void TGAImage::set(int x, int y, const Color &c) {
            TGAColor tc = TGAColor(c);
            memcpy(data.data() + (x + y * w) * bpp, tc.bgra, bpp);
        }

        void TGAImage::set(int x, int y, float z, const Color &c) {
            TGAColor tc = TGAColor(c);
            memcpy(data.data() + (x + y * w) * bpp, tc.bgra, bpp);
            depth[y * w + x] = z;
        }

        void TGAImage::set(int x, int y, const TGAColor &c) {
            memcpy(data.data() + (x + y * w) * bpp, c.bgra, bpp);
        }
    
        void TGAImage::clear() {
            std::fill(depth.begin(), depth.end(), std::numeric_limits<float>::max());
        }
    
        void TGAImage::flip_horizontally() {
            for (int i = 0; i < w / 2; i++)
                for (int j = 0; j < h; j++)
                    for (int b = 0; b < bpp; b++)
                        std::swap(data[(i + j * w) * bpp + b], data[(w - 1 - i + j * w) * bpp + b]);
        }
    
        void TGAImage::flip_vertically() {
            for (int i = 0; i < w; i++)
                for (int j = 0; j < h / 2; j++)
                    for (int b = 0; b < bpp; b++)
                        std::swap(data[(i + j * w) * bpp + b], data[(i + (h - 1 - j) * w) * bpp + b]);
        }
    
        void TGATarget::present() {
            fb.write_tga_file(filename);
        }
    
        //! On TGATarget, rewrites the whole
        void TGATarget::present_depth() {
            // Writing the depth value (z-value) as color, instead of the actual color
            for(int x = 0; x < fb.width(); x++) {
                for(int y = 0; y < fb.height(); y++) {
                    uint8_t intensity = static_cast<uint8_t>(
                        fb.get_z(x, y) * Color::MAX_COLOR_CHANNEL
                    );
                    Color c = {intensity, intensity, intensity, Color::MAX_COLOR_CHANNEL};
                    fb.set(x, y, c);
                }
            }
            
            fb.write_tga_file(filename);
        }
    }    
}
