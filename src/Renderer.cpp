#include "Renderer.h"

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

std::vector<std::string> skyboxFaces = {
	
	"textures/skybox/left.jpg",
	"textures/skybox/right.jpg",
	"textures/skybox/top.jpg",
	"textures/skybox/bottom.jpg",
	"textures/skybox/front.jpg",
	"textures/skybox/back.jpg"
};


Renderer::Renderer(Camera* cam) {
	m_pCamera = cam;
	VAO_object = 0;
	VAO_skybox = 0;
	VBO_position = 0;
	VBO_texture = 0;
	EBO = 0;
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO_skybox);
	glDeleteVertexArrays(1, &VAO_object);
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &VBO_texture);
}

void Renderer::start() {

	shader_render = new Shader("src/shader/obj_render.vert", "src/shader/obj_render.frag");
	shader_skybox = new Shader("src/shader/skybox.vert", "src/shader/skybox.frag");

	MeshLoader meshLoader;

	m_mesh = meshLoader.loadMesh("data/trailer-3.obj");

	m_meshSize = m_mesh.positions.size();

	// Textures
	texture = new Texture("textures/test.png", GL_TEXTURE_2D);
	texture2 = new Texture("textures/test2.png", GL_TEXTURE_2D);
	texture3 = new Texture("textures/test3.png", GL_TEXTURE_2D);
	texture4 = new Texture("textures/test4.png", GL_TEXTURE_2D);
	texture5 = new Texture("textures/test5.png", GL_TEXTURE_2D);

	// Background
	m_skybox = new Texture(skyboxFaces, GL_TEXTURE_CUBE_MAP);

	glGenVertexArrays(1, &VAO_object);
	glGenVertexArrays(1, &VAO_skybox);

	glGenBuffers(1, &VBO_position);
	glGenBuffers(1, &VBO_texture);
	glGenBuffers(1, &VBO_skybox);
	glGenBuffers(1, &EBO);  

	// === Object VAO Setup ===
	glBindVertexArray(VAO_object);

	// Position buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, m_meshSize * sizeof(glm::vec3), m_mesh.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// TexCoord buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
	glBufferData(GL_ARRAY_BUFFER, m_meshSize * sizeof(glm::vec2), m_mesh.texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(1);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.indices.size() * sizeof(unsigned int), m_mesh.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0); // Finish object VAO

	// === Skybox VAO Setup ===
	glBindVertexArray(VAO_skybox);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Finish skybox VAO

	std::cout << "Rendering " << m_meshSize << " points.\n";
	std::cout << "sizeof(Point): " << sizeof(Mesh) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::render()
{
	RenderText();

	glm::mat4 view_skybox = glm::mat4(glm::mat3(m_pCamera->GetViewMatrix()));
	glm::mat4 projection_skybox = glm::perspective(glm::radians(m_pCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	// PASS 1: Render skybox
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	shader_skybox->use();

	glUniformMatrix4fv(glGetUniformLocation(shader_skybox->ID, "view"), 1, GL_FALSE, glm::value_ptr(view_skybox));
	glUniformMatrix4fv(glGetUniformLocation(shader_skybox->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projection_skybox));

	glBindVertexArray(VAO_skybox);

	//bind skybox
	m_skybox->bind_texture(0);
	glUniform1i(glGetUniformLocation(shader_skybox->ID, "skybox"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);


	// PASS 2: Render object

	glEnable(GL_DEPTH_TEST);

	glm::mat4 view_object = m_pCamera->GetViewMatrix();
	glm::mat4 projection_object = glm::perspective(glm::radians(m_pCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	shader_render->use();

	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "view"), 1, GL_FALSE, glm::value_ptr(view_object));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projection_object));

	glBindVertexArray(VAO_object);

	texture->bind_texture(1);
	texture2->bind_texture(2);
	texture3->bind_texture(3);
	texture4->bind_texture(4);
	texture5->bind_texture(5);

	glUniform1i(glGetUniformLocation(shader_render->ID, "tex"), m_textureSlot);
	glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::RenderText()
{
	glUseProgram(0);

	// Set up orthographic projection for 2D screen-space rendering (e.g., text)
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCR_WIDTH, SCR_HEIGHT, 0, -1, 1);

	float fps = 1.0;

	std::stringstream ss;
	ss << "FPS: " << fps << "\n Tris: " << m_mesh.indices.size();
	std::string text = ss.str();

	static char buffer[99999];
	int num_quads = stb_easy_font_print(20, 20, (char*)text.c_str(), NULL, buffer, sizeof(buffer));

	glColor3f(1.0f, 1.0f, 0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
