#include "clip.hpp"

namespace vkr {

    // Just a middleware structure to make the plane clipping
    struct Polygon {
        constexpr static int MAX_VERT = 9;
        
        Vertex vert[MAX_VERT];
        int size = 0;
    };
    
    ClipResult clip(Triangle t) {
        // TODO:
    }

} // namespace vkr
