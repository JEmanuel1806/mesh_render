#pragma once

#include "Camera.h"
#include "Shader.h" 

#include "MeshLoader.h"
#include "Texture.h"

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

class Renderer {

public:
	Renderer(Camera* camera);
	~Renderer();

	void start();
	void render();

	int m_meshSize;
	unsigned int m_textureSlot = 0;

	void switchTexture(bool direction) {
		if (direction)
			m_textureSlot = (m_textureSlot + 1) % 5;
		else
			m_textureSlot = (m_textureSlot - 1) % 5;
	}


private:
	Camera* m_pCamera;
	Mesh m_mesh;
	Texture *texture, *texture2, *texture3, *texture4, *texture5;
	Texture* m_skybox;
	Shader* shader_render, *shader_skybox;
	GLuint VAO_object, VAO_skybox, VBO_position, VBO_texture, VBO_skybox; 
	GLuint EBO;

	void RenderText();


};