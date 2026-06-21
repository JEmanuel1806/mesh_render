#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const float intensity)
    : Light(color, intensity), m_direction(direction)
{
}

const glm::vec3& DirectionalLight::getDirection() const {
    return m_direction;
}

void DirectionalLight::setDirection(const glm::vec3& dir) {
    m_direction = dir;
}
