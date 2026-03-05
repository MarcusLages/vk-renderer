#include <fstream>
#include <sstream>
#include "model.hpp"
#include <iostream>

namespace vkr {

    // Adaptation from tinyrenderer by ssloy
    Model::Model(const std::string filename, float min_vrange, float max_vrange)
    : vert_range(min_vrange, max_vrange) {
        std::ifstream in;
        in.open(filename, std::ifstream::in);
        if (in.fail()) return;

        std::string line;
        while (!in.eof()) {
            std::getline(in, line);
            std::istringstream iss(line.c_str());

            char trash;
            if (!line.compare(0, 2, "v ")) {
                iss >> trash;
                mvmath::vec3 v;
                for (int i : {0,1,2}) iss >> v[i];
                vertices.push_back(v);
            } else if (!line.compare(0, 2, "f ")) {
                int f,t,n, cnt = 0;
                iss >> trash;
                while (iss >> f >> trash >> t >> trash >> n) {
                    faces.push_back(--f);
                    cnt++;
                }
                if (3!=cnt) {
                    std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                    return;
                }
            }
        }
        std::cerr << "# v# " << verts_len() << " f# "  << faces_len() << std::endl;
    }

}