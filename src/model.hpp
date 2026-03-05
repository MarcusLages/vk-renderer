#pragma once
#include <vector>
#include <string>
#include "mvmath.hpp"

namespace vkr {
    
    // Adaptation from tinyrenderer by ssloy
    class Model {
        std::vector<mvmath::vec3> vertices = {};
        std::vector<int> faces = {};

    public:
        Model(const std::string filename);
        
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