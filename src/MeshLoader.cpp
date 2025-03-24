#include "MeshLoader.h"

#include <unordered_map>

Mesh MeshLoader::loadMesh(std::string filepath)
{
    Mesh obj_mesh;
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texcoords;
    std::unordered_map<Vertex, unsigned int> uniqueVertices;

    std::string line;
    std::ifstream obj_file(filepath);
    if (!obj_file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return obj_mesh;
    }

    while (std::getline(obj_file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "v") {
            glm::vec3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            temp_positions.push_back(pos);
        }
        else if (key == "vt") {
            glm::vec2 uv;
            iss >> uv.x >> uv.y;
            temp_texcoords.push_back(uv);
        }
        else if (key == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (key == "f") {
            for (int i = 0; i < 3; ++i) {
                std::string vertexStr;
                iss >> vertexStr;

                std::istringstream vss(vertexStr);
                std::string v, t, n;
                std::getline(vss, v, '/');
                std::getline(vss, t, '/');
                std::getline(vss, n, '/');

                Vertex vertex;
                vertex.position = temp_positions[std::stoi(v) - 1];
                vertex.texCoord = t.empty() ? glm::vec2(0.0f) : temp_texcoords[std::stoi(t) - 1];
                vertex.normal = n.empty() ? glm::vec3(0.0f) : temp_normals[std::stoi(n) - 1];

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<unsigned int>(obj_mesh.positions.size());
                    obj_mesh.positions.push_back(vertex.position);
                    obj_mesh.texCoords.push_back(vertex.texCoord);
                    obj_mesh.normals.push_back(vertex.normal);
                }

                obj_mesh.indices.push_back(uniqueVertices[vertex]);
            }
        }
    }

    return obj_mesh;
}

