#pragma once

#include "Light.h"
#include <glm/glm.hpp>

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const float intensity);

    const glm::vec3& getDirection() const;
    void setDirection(const glm::vec3& dir);

private:
    glm::vec3 m_direction;
};
