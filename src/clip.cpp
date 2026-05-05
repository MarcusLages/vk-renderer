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
        return !(mvmath::is_equalf(t.a.clip.w, 0) ||
                 mvmath::is_equalf(t.b.clip.w, 0) ||
                 mvmath::is_equalf(t.c.clip.w, 0));
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
            if(t[i].clip.z < -t[i].clip.w)     // Looks backwards, but don't forget z is negative here
                cur |= (CSConst::FAR);
            if(t[i].clip.z > 0)
                cur |= (CSConst::NEAR);
        }

        return res;
    }

    // If, throughout all the vertices, the same n bit is 1, then the whole 
    // triangle is outside
    //      E.g.: [0b001011, 0b101000, 0b001000]
    //            The fourth digit is 1 in every single one of the vertices, 
    //            which means that the whole triangle is out
    // Must: cs_consts.size() == 3
    bool is_triangle_outside(std::vector<int>& cs_consts) {
        for(int i = 0; i < CSConst::BITS; i++) {
            int mask = 1 << i;
            if(mask & cs_consts[0] & cs_consts[1] & cs_consts[2])
                return true;
        }
        return false;
    }
    
    ClipReturn clip(Triangle& t) {
        std::vector<Triangle> res;
        
        // Degenerate division by 0 on z-division
        if(!is_valid_clip_triangle(t))
            return ClipReturn(false, res);

        std::vector<int> cs_consts = get_cs_consts(t);

        // Case 1: all vertices inside; accept triangle; no clipping
        if(cs_consts[0] == 0 &&
           cs_consts[1] == 0 &&
           cs_consts[2] == 0) {
            res.push_back(t);
            return ClipReturn(true, res);
        }

        // Case 2: all vertices outside; reject triangle; no clipping
        if(is_triangle_outside(cs_consts))
            return ClipReturn(false, res);

        // TODO
    }

} // namespace vkr
