#pragma once

#include "Camera.h"
#include "Shader.h" 

#include "MeshLoader.h"
#include "Texture.h"

#include "DirectionalLight.h"

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

class Renderer {

public:
	Renderer(Camera* camera);
	~Renderer();

	void start();
	void render(const float fps);

	int m_meshSize;
	glm::vec3 m_rotationValue;
	unsigned int m_textureSlot = 1;

	void switchTexture(bool direction) {
		if (direction)
			m_textureSlot = (m_textureSlot + 1) % 5;
		else
			m_textureSlot = (m_textureSlot - 1) % 5;
	}

	void rotateLight(bool clockwise) {
		float angle = clockwise ? -0.1f : 0.1f;

		glm::vec3 dir = dirLight->getDirection();
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 1.0, 0.0));
		dir = glm::vec3(rot * glm::vec4(dir, 0.0f));

		dirLight->setDirection(glm::normalize(dir));
	}

	void rotateLightMouse(float deltaX, float deltaY) {
		const float sensitivity = 0.003f;
		const glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

		glm::vec3 dir = glm::normalize(dirLight->getDirection());

		glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f),-deltaX * sensitivity,worldUp);
		dir = glm::normalize(glm::vec3(yawRotation * glm::vec4(dir, 0.0f)));

		glm::vec3 right = glm::normalize(glm::cross(dir, worldUp));
		glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), -deltaY * sensitivity, right);
		glm::vec3 pitchedDir = glm::normalize(glm::vec3(pitchRotation * glm::vec4(dir, 0.0f)));

		if (glm::abs(glm::dot(pitchedDir, worldUp)) < 0.98f)
			dir = pitchedDir;

		dirLight->setDirection(dir);
	}


private:
	Camera* m_pCamera;
	Mesh m_mesh;
	Texture *texture, *texture2, *texture3, *texture4, *texture5;
	Texture* textureGround;
	Texture* m_skybox;
	GLuint m_depthTex;
	Shader* shader_render, *shader_skybox, *shader_depth, *shader_depth_debug;

	GLuint m_vaoObj, m_vboObj, m_vboObjTex, m_vboObjNrml;
	GLuint m_vaoSky, m_vboSky;
	GLuint m_vaoPlane, m_vboPlane, m_vboPlaneTex, m_vboPlaneNrml;
	GLuint m_vaoQuad, m_vboQuad;
	GLuint m_ebo;
	GLuint m_depthFBO;

	DirectionalLight* dirLight;

	void RenderText(const float fps);


};
