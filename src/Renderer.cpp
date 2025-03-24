#include "Renderer.h"


Renderer::Renderer(Camera* cam) {
	camera = cam;
	VAO = 0;
	VBO_position = 0;
	VBO_texture = 0;
	EBO = 0;
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &VBO_texture);
}

void Renderer::start() {

	shader_render = new Shader("src/shader/obj_render.vert", "src/shader/obj_render.frag");

	MeshLoader meshLoader;

	mesh = meshLoader.loadMesh("data/trailer-3.obj");

	mesh_size = mesh.positions.size();

	texture = new Texture("textures/test.png",GL_TEXTURE_2D);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_position);
	glGenBuffers(1, &VBO_texture);
	glBindVertexArray(VAO);

	//position buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, mesh_size * sizeof(glm::vec3), mesh.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);                        // position
	glEnableVertexAttribArray(0);


	//texture buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
	glBufferData(GL_ARRAY_BUFFER, mesh_size * sizeof(glm::vec2), mesh.texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(1);

	//EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

	std::cout << "Rendering " << mesh_size << " points.\n";
	std::cout << "sizeof(Point): " << sizeof(Mesh) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::render()
{
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader_render->use();

	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	texture->bind_texture(0);
	glUniform1i(glGetUniformLocation(shader_render->ID, "tex"), 0);
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

