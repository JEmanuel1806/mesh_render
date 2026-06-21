#include "Light.h"

Light::Light(const glm::vec3& color, const float intensity)
    : m_color(color), m_intensity(intensity)
{
}

const glm::vec3& Light::getColor() const {
    return m_color;
}

const float Light::getIntensity() const {
    return m_intensity;
}

void Light::setColor(const glm::vec3& color) {
    m_color = color;
}

void Light::setIntensity(const float intensity) {
    m_intensity = intensity;
}
