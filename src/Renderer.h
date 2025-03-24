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

private:
	Camera* camera;
	Mesh mesh;
	Texture* texture;
	Shader* shader_render;
	GLuint VAO, VBO_position, VBO_texture; 
	GLuint EBO;
};