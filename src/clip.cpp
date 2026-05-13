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
        BITS    = 6,
        TOTAL   = BITS
    };

    // ? Wraps around
    CSConst next_plane_const(CSConst cs) {
        if(cs >= CSConst::LAST)
            return CSConst::FIRST;
        else
            return CSConst(static_cast<int>(cs) << 1);
    }

    bool is_outside_plane(CSConst cs, Vertex v) {
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
                return v.clip.z > v.clip.w;
            case CSConst::NEAR:
                return v.clip.z < 0;
            default: _UNREACHABLE();
        }
    }
    
    float plane_lerp_get_t(CSConst cs, Vertex prev, Vertex cur) {
        const mvmath::vec4 a = prev.clip;
        const mvmath::vec4 b = cur.clip;
        switch(cs) {
            case CSConst::ABOVE:
                return (a.w - a.y) / ((b.y - a.y) - (b.w - a.w));
            case CSConst::BELOW:
                return (a.w + a.y) / ((a.w + a.y) - (b.w + b.y));
            case CSConst::RIGHT:
                return (a.w - a.x) / ((b.x - a.x) - (b.w - a.w));
            case CSConst::LEFT:
                return (a.w + a.x) / ((a.w + a.x) - (b.w + b.x));
            case CSConst::FAR:
                return (a.w - a.z) / ((b.z - a.z) - (b.w - a.w));
            case CSConst::NEAR:
                if(mvmath::is_equalf(a.z, b.z)) return 0;
                return - a.z / (b.z - a.z); // Different because z is in [0, +1]
            default: _UNREACHABLE();
        }
    }

    // Point on the line from prev to cur which intersects the limiting plane
    Vertex plane_intersect(CSConst cs, Vertex prev, Vertex cur) {
        float t = plane_lerp_get_t(cs, prev, cur);
        
        float t_rem = 1 - t;
        mvmath::vec4 inter = {
            t_rem * prev.clip.x + t * cur.clip.x,
            t_rem * prev.clip.y + t * cur.clip.y,
            t_rem * prev.clip.z + t * cur.clip.z,
            t_rem * prev.clip.w + t * cur.clip.w
        };
        return Vertex(inter);
    }
    
    // Used by clipper
    // Returns the Cohen-Sutherland number as CSConst
    std::vector<int> get_cs_consts(Triangle& t) {
        std::vector<int> res = {0, 0, 0};

        for(int i = Triangle::Idx::A; i <= Triangle::Idx::C; i++) {
            int& cur = res[i];

            CSConst cs_plane = CSConst::FIRST;
            for(int j = 0; j < CSConst::TOTAL; j++) {
                if(is_outside_plane(cs_plane, t[i]))
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


        // Case 3: clip triangle on the 6 planes of the frustrum of:
        //         <[left, right], [down, up], [near, far]>
        //         <[-w, +w], [-w, +w], [0, +w]>
        std::vector<Vertex> in_polygon(3), out_polygon;
        in_polygon[0] = t.a;
        in_polygon[1] = t.b;
        in_polygon[2] = t.c;

        CSConst cs_plane = CSConst::FIRST;
        for(int i = 0; i < CSConst::TOTAL; i++) {
            out_polygon = std::vector<Vertex>();
            Vertex cur, prev;

            for(int j = 0; j < in_polygon.size(); j++) {
                // ? Have to add the size so there's no negative modulo causing wrong indexes
                int prev_idx = (in_polygon.size() + j - 1) % in_polygon.size();
                cur = in_polygon[j];
                prev = in_polygon[prev_idx];

                bool cur_inside = !is_outside_plane(cs_plane, cur);
                bool prev_inside = !is_outside_plane(cs_plane, prev);

                if(cur_inside) {
                    if(prev_inside) {
                        // Case 1: both inside
                        out_polygon.push_back(cur);
                    } else {
                        // Case 2: cur inside, prev outside (entering visible space)
                        Vertex intersect = plane_intersect(cs_plane, prev, cur);
                        out_polygon.push_back(intersect);
                        out_polygon.push_back(cur);
                    }
                } else {
                    if(prev_inside) {
                        // Case 2: cur outside, prev inside (exiting visible space)
                        Vertex intersect = plane_intersect(cs_plane, prev, cur);
                        out_polygon.push_back(intersect);
                    }
                    // Case 4: both outside (ignores vertex)
                }
            }

            in_polygon = out_polygon;
            cs_plane = next_plane_const(cs_plane);
        }

        // Create the output triangle list from the out_polygon
        for(int i = 1; i < out_polygon.size() - 1; i++) {
            Triangle t(out_polygon[0], out_polygon[i], out_polygon[i + 1]);
            res.push_back(t);
        }
        return ClipReturn(true, res);
    }

} // namespace vkr
