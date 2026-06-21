#pragma once

#include <vector>

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class LightManager
{
public:
	std::vector<DirectionalLight> dirLights;
	std::vector<PointLight> pointLights;

	void applyLights(Shader& shader);

};

