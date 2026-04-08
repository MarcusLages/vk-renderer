#pragma once
#include <vector>
#include <string>
#include "transform.hpp"
#include "mvmath.hpp"

namespace vkr {
    
    // Adaptation from tinyrenderer by ssloy
    // TODO: change code later to make faces store triples
    class Model {
        std::vector<mvmath::vec3> vertices = {};
        std::vector<int> faces = {};
        Transform transform;
        
    public:
        const std::tuple<float, float> vert_range = {}; // Min-max of vertex coordinates (def = {-1, 1})
        
        Model(const std::string filename, float min_vrange = -1, float max_vrange = 1);
        
        constexpr mvmath::vec3 vert(const int i) const { 
            return vertices[i]; 
        }

        constexpr mvmath::vec3 vert(const int face, const int vert) const {
            return vertices[faces[face * 3 + vert]];
        }

        inline mvmath::mat4 model_mat() {
            return transform.model_mat();
        }

        constexpr int verts_len() const { return vertices.size(); }
        constexpr int faces_len() const { return faces.size() / 3; }
    };
    
} // namespace vkr