#pragma once

#include "Camera.h"
#include "Shader.h" 

#include "MeshLoader.h"



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
	Shader* shader_render;
	GLuint VAO, VBO; 
	GLuint EBO;
};