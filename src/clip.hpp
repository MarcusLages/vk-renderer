#pragma once
#include "primitives.hpp"

namespace vkr {
    
    // Structure used as return from Clip to avoid slow std::vector construction
    struct ClipResult {
        constexpr static int MAX_TRIANGLES = 7; 
        
        Triangle ret[MAX_TRIANGLES];
        int size = 0;
    };
    
    ClipResult clip(Triangle t);
    
} // namespace vkr
