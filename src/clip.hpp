#pragma once
#include <vector>
#include "primitives.hpp"

namespace vkr {

    // TODO: Structure used as return from Clip to avoid slow std::vector construction
    // TODO: I will just use std::vector for now
    // struct ClipResult {
    //     constexpr static int MAX_TRIANGLES = 7; 
        
    //     Triangle ret[MAX_TRIANGLES];
    //     int size = 0;

    //     constexpr ClipResult() = default;
    // };
    
    std::vector<Triangle> clip(Triangle& t);
    
} // namespace vkr
