#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

class Light {
public:
    Light(const glm::vec3& color, const float intensity);
    virtual ~Light() = default;

    const glm::vec3& getColor() const;
    const float getIntensity() const;

    void setColor(const glm::vec3& color);
    void setIntensity(const float intensity);

protected:
    glm::vec3 m_color;
    float m_intensity;
};
