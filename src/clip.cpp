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

    // Used to check if all w != 0 to not cause 0 division
    bool is_valid_clip_triangle(Triangle& t) {
        return mvmath::is_equalf(t.a.clip.w, 0) &&
               mvmath::is_equalf(t.b.clip.w, 0) &&
               mvmath::is_equalf(t.c.clip.w, 0);
    }
    
    // Used by clipper
    // Returns the Cohen-Sutherland number as CSConst
    std::vector<int> get_cs_consts(Triangle& t) {
        std::vector<int> res = {0, 0, 0};

        for(int i = Triangle::Idx::A; i <= Triangle::Idx::C; i++) {
            int& cur = res[i];

            if(t[i].clip.y > t[i].clip.w)
                cur |= (CSConst::ABOVE);
            if(t[i].clip.y < -t[i].clip.w)
                cur |= (CSConst::BELOW);
            if(t[i].clip.x > t[i].clip.w)
                cur |= (CSConst::RIGHT);
            if(t[i].clip.x < -t[i].clip.w)
                cur |= (CSConst::LEFT);
            if(t[i].clip.z < t[i].clip.w)     // Looks backwards, but don't forget z is negative here
                cur |= (CSConst::FAR);
            if(t[i].clip.z > 0)
                cur |= (CSConst::NEAR);
        }

        return res;
    }
    
    ClipReturn clip(Triangle& t) {
        std::vector<Triangle> res;
        
        // Degenerate division by 0 on z-division
        if(!is_valid_clip_triangle(t)) {
            return ClipReturn(false, res);
        }

        std::vector<int> cs_consts = get_cs_consts(t);

        // Case 1: all vertices inside; accept triangle; no clipping
        if(cs_consts[0] == 0 &&
           cs_consts[1] == 0 &&
           cs_consts[2] == 0) {
            res.push_back(t);
            return ClipReturn(true, res);
        }

        // TODO
    }

} // namespace vkr
