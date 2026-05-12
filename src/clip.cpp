#include <cmath>
#include "unreachable.hpp"
#include "clip.hpp"

namespace vkr {

    // Cohen-Sutherland number constants
    enum CSConst {
        ABOVE   = 0b000001,
        BELOW   = 0b000010,
        RIGHT   = 0b000100,
        LEFT    = 0b001000,
        FAR     = 0b010000,
        NEAR    = 0b100000,
        FIRST   = ABOVE,
        LAST    = NEAR,
        BITS = 6
    };

    CSConst next_plane_const(CSConst cs) {
        if(cs >= CSConst::LAST)
            return CSConst::FIRST;
        else
            return CSConst(static_cast<int>(cs) << 1);
    }

    bool compare_plane(CSConst cs, Vertex v) {
        switch(cs) {
            case CSConst::ABOVE:
                return v.clip.y > v.clip.w;
            case CSConst::BELOW:
                return v.clip.y < -v.clip.w;
            case CSConst::RIGHT:
                return v.clip.x > v.clip.w;
            case CSConst::LEFT:
                return v.clip.x < -v.clip.w;
            case CSConst::FAR:
                return v.clip.z < -v.clip.w; // Perspective does looks backwards, but don't forget z is negative here
            case CSConst::NEAR:
                return v.clip.z > 0;
            default: _UNREACHABLE();
        }
    }

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

            CSConst cs_plane = CSConst::FIRST;
            for(int j = 0; j < CSConst::BITS; j++) {
                if(compare_plane(cs_plane, t[i]))
                    cur |= cs_plane;
                    
                cs_plane = next_plane_const(cs_plane);
            }
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
    
    // Uses a modified Sutherland-Hodgman polygon clipping algorithm
    ClipReturn clip(Triangle& t) {
        std::vector<Triangle> res;
        
        // TODO: only here for now
        //       will take care of that on a later step, only here to avoid crashes
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
