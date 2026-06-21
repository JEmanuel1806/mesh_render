#pragma once

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Vertex {
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texCoord;

    bool operator==(const Vertex& other) const {
        return m_position == other.m_position &&
            m_normal == other.m_normal &&
            m_texCoord == other.m_texCoord;
    }
};

namespace std {
    template <>
    struct hash<Vertex> {
        size_t operator()(const Vertex& v) const {
            return hash<float>()(v.m_position.x) ^
                hash<float>()(v.m_position.y) ^
                hash<float>()(v.m_position.z);
        }
    };
}


class Mesh {
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;
private:
};