#pragma once

#include "Camera.h"
#include "Shader.h" 

#include "MeshLoader.h"
#include "Texture.h"



class Renderer {

public:
	Renderer(Camera* camera);
	~Renderer();

	void start();
	void render();

	int mesh_size;
	unsigned int texture_slot = 0;

	void switchTexture(bool direction) {
		if (direction)
			texture_slot = (texture_slot + 1) % 5;
		else
			texture_slot = (texture_slot - 1) % 5;
	}

private:
	Camera* camera;
	Mesh mesh;
	Texture *texture, *texture2, *texture3, *texture4, *texture5;
	Shader* shader_render;
	GLuint VAO, VBO_position, VBO_texture; 
	GLuint EBO;
};