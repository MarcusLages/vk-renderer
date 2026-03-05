#pragma once
#include <vector>
#include <string>
#include "mvmath.hpp"

namespace vkr {
    
    // Adaptation from tinyrenderer by ssloy
    // TODO: change code later to make faces store triples
    class Model {
        std::vector<mvmath::vec3> vertices = {};
        std::vector<int> faces = {};
        
    public:
        const std::tuple<float, float> vert_range = {}; // Min-max of vertex coordinates (def = {-1, 1})
        
        Model(const std::string filename, float min_vrange = -1, float max_vrange = 1);
        
        mvmath::vec3 vert(const int i) const { 
            return vertices[i]; 
        }
        mvmath::vec3 vert(const int face, const int vert) const {
            return vertices[faces[face * 3 + vert]];
        }

        const int verts_len() const { return vertices.size(); }
        const int faces_len() const { return faces.size() / 3; }
    };
    
} // namespace vkr