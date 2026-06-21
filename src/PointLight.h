#pragma once
#include "Light.h"
class PointLight :
    public Light
{
    glm::vec3 position;

    //void applyLight(Shader& shader, int id = 0) override;
};

