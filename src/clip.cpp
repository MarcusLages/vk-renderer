#include <cmath>
#include "clip.hpp"

namespace vkr {

    // Cohen-Sutherland number constants
    enum CSConst {
        ABOVE   = 0b0000001,
        BELOW   = 0b0000010,
        RIGHT   = 0b0000100,
        LEFT    = 0b0001000,
        FAR     = 0b0010000,
        NEAR    = 0b0100000,
        BITS = 6
    };
    
    // Used by clipper
    // Returns the Cohen-Sutherland number
    // Bits 0-5: a
    // Bits 6-11: b
    // Bits 12-17: c
    int is_inside_cs(Vertex& v) {
        int res = 0;
        int bitshift = 0;

        for(int i = Triangle::Idx::A; i <= Triangle::Idx::C; i++) {
            if(v.clip.y > v.clip.w)
                res |= (CSConst::ABOVE << bitshift);
            if(v.clip.y < -v.clip.w)
                res |= (CSConst::BELOW << bitshift);
            if(v.clip.x > v.clip.w)
                res |= (CSConst::RIGHT << bitshift);
            if(v.clip.x < -v.clip.w)
                res |= (CSConst::LEFT << bitshift);
            if(v.clip.z < v.clip.w)
                res |= (CSConst::FAR << bitshift);
            if(v.clip.z > 0)
                res |= (CSConst::NEAR << bitshift);

            bitshift += CSConst::BITS;
        }
        
        return res;
    }
    
    ClipReturn clip(Triangle& t) {
        // Degenerate division by 0 on z-division
        if(!t.is_valid()) {
            return ClipReturn(false, std::vector<Triangle>());
        }

        // TODO
    }

} // namespace vkr
