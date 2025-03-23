#include "MeshLoader.h"

Mesh MeshLoader::loadMesh(std::string filepath)
{
    Mesh obj_mesh;
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
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            obj_mesh.positions.push_back(position);
        }
        else if (key == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            obj_mesh.normals.push_back(normal);
        }
        else if (key == "f") {
            std::string v1, v2, v3;
            iss >> v1 >> v2 >> v3;

            auto extractVertexIndex = [](const std::string& token) {
                size_t pos = token.find('/');
                return std::stoi(token.substr(0, pos)) - 1;
                };

            obj_mesh.indices.push_back(extractVertexIndex(v1));
            obj_mesh.indices.push_back(extractVertexIndex(v2));
            obj_mesh.indices.push_back(extractVertexIndex(v3));
        }
    }

    return obj_mesh;
}
