#include "Renderer.h"

float scale = 10.0f; // repeat 10x


float skyboxVertices[] = {     
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

float planeVertices[] = {      
	-125.0f, 0.0f,  125.0f,
	 125.0f, 0.0f,  125.0f,
	-125.0f, 0.0f, -125.0f,			  
	 125.0f, 0.0f,  125.0f,
	 125.0f, 0.0f, -125.0f,
	-125.0f, 0.0f, -125.0f
};


float planeTexCoords[] = {
	0.0f,      scale,
	scale,     scale,
	0.0f,      0.0f,
	scale,     scale,
	scale,     0.0f,
	0.0f,      0.0f
};

float planeNormals[] = {
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

float quadVertices[] = {
	-1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, 1.0f, 1.0f
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
	texture = nullptr;
	texture2 = nullptr;
	texture3 = nullptr;
	texture4 = nullptr;
	texture5 = nullptr;
	textureGround = nullptr;
	m_skybox = nullptr;
	shader_render = nullptr;
	shader_skybox = nullptr;
	shader_depth = nullptr;
	shader_depth_debug = nullptr;
	shader_ssao_calc = nullptr;
	shader_ssao_blur = nullptr;
	shader_final = nullptr;
	dirLight = nullptr;
	m_vaoObj = 0;
	m_vaoSky = 0;
	m_vaoPlane = 0;
	m_vaoQuad = 0;
	m_vboObj = 0;
	m_vboObjTex = 0;
	m_vboObjNrml = 0;
	m_vboSky = 0;
	m_vboPlane = 0;
	m_vboPlaneTex = 0;
	m_vboPlaneNrml = 0;
	m_vboQuad = 0;
	m_ebo = 0;
	m_fboShadowMap = 0;
	m_fboScene = 0;
	m_fboSSAO = 0;
	m_fboBlur = 0;
	m_shadowTex = 0;
	m_gColorTex = 0;
	m_gNormalTex = 0;
	m_gPosTex = 0;
	m_gDepthTex = 0;
	m_ssaoTex = 0;
	m_ssaoBlurTex = 0;
	m_noiseTex = 0;
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &m_vaoSky);
	glDeleteVertexArrays(1, &m_vaoObj);
	glDeleteVertexArrays(1, &m_vaoPlane);
	glDeleteVertexArrays(1, &m_vaoQuad);
	glDeleteBuffers(1, &m_vboObj);
	glDeleteBuffers(1, &m_vboObjTex);
	glDeleteBuffers(1, &m_vboObjNrml);
	glDeleteBuffers(1, &m_vboPlane);
	glDeleteBuffers(1, &m_vboPlaneTex);
	glDeleteBuffers(1, &m_vboPlaneNrml);
	glDeleteBuffers(1, &m_vboSky);
	glDeleteBuffers(1, &m_vboQuad);
	glDeleteBuffers(1, &m_ebo);
	glDeleteFramebuffers(1, &m_fboShadowMap);
	glDeleteFramebuffers(1, &m_fboScene);
	glDeleteFramebuffers(1, &m_fboSSAO);
	glDeleteFramebuffers(1, &m_fboBlur);
	glDeleteTextures(1, &m_shadowTex);
	glDeleteTextures(1, &m_gColorTex);
	glDeleteTextures(1, &m_gNormalTex);
	glDeleteTextures(1, &m_gPosTex);
	glDeleteTextures(1, &m_gDepthTex);
	glDeleteTextures(1, &m_ssaoTex);
	glDeleteTextures(1, &m_ssaoBlurTex);
	glDeleteTextures(1, &m_noiseTex);
	delete texture;
	delete texture2;
	delete texture3;
	delete texture4;
	delete texture5;
	delete textureGround;
	delete m_skybox;
	delete shader_render;
	delete shader_skybox;
	delete shader_depth;
	delete shader_depth_debug;
	delete shader_ssao_calc;
	delete shader_ssao_blur;
	delete shader_final;
	delete dirLight;
}

void Renderer::start() {

	shader_depth = new Shader("src/shader/depth_render.vert", "src/shader/depth_render.frag");
	shader_depth_debug = new Shader("src/shader/depth_debug.vert", "src/shader/depth_debug.frag");
	shader_render = new Shader("src/shader/scene_render.vert", "src/shader/scene_render.frag");
	shader_skybox = new Shader("src/shader/skybox.vert", "src/shader/skybox.frag");
	shader_ssao_calc = new Shader("src/shader/ssao_calc.vert", "src/shader/ssao_calc.frag");
	shader_ssao_blur = new Shader("src/shader/ssao_blur.vert", "src/shader/ssao_blur.frag");
	shader_final = new Shader("src/shader/final_render.vert", "src/shader/final_render.frag");

	MeshLoader meshLoader;

	m_mesh = meshLoader.loadMesh("data/trailer60s.obj");

	m_meshSize = m_mesh.positions.size();

	texture = new Texture("textures/test.png", GL_TEXTURE_2D);
	texture2 = new Texture("textures/test2.png", GL_TEXTURE_2D);
	texture3 = new Texture("textures/test3.png", GL_TEXTURE_2D);
	texture4 = new Texture("textures/test4.png", GL_TEXTURE_2D);
	texture5 = new Texture("textures/test5.png", GL_TEXTURE_2D);

	textureGround = new Texture("textures/env/concrete-light.jpg", GL_TEXTURE_2D);

	// Lights
	dirLight = new DirectionalLight(
		glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f)),
		glm::vec3(1.0f),
		1.0f
	);

	// Background
	m_skybox = new Texture(skyboxFaces, GL_TEXTURE_CUBE_MAP);

	glGenVertexArrays(1, &m_vaoObj);
	glGenVertexArrays(1, &m_vaoSky);
	glGenVertexArrays(1, &m_vaoPlane);
	glGenVertexArrays(1, &m_vaoQuad);

	glGenBuffers(1, &m_vboObj);
	glGenBuffers(1, &m_vboObjTex);
	glGenBuffers(1, &m_vboObjNrml);
	glGenBuffers(1, &m_vboSky);
	glGenBuffers(1, &m_vboPlane);
	glGenBuffers(1, &m_vboPlaneTex);
	glGenBuffers(1, &m_vboPlaneNrml);
	glGenBuffers(1, &m_ebo);  
	glGenBuffers(1, &m_vboQuad);

	// VAO setup for trailer
	glBindVertexArray(m_vaoObj);

	// Position buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboObj);
	glBufferData(GL_ARRAY_BUFFER, m_meshSize * sizeof(glm::vec3), m_mesh.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// TexCoord buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboObjTex);
	glBufferData(GL_ARRAY_BUFFER, m_meshSize * sizeof(glm::vec2), m_mesh.texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(1);

	// Normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboObjNrml);
	glBufferData(GL_ARRAY_BUFFER, m_meshSize * sizeof(glm::vec3), m_mesh.normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.indices.size() * sizeof(unsigned int), m_mesh.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	// VAO setup for quad
	glBindVertexArray(m_vaoQuad);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// VAO for skybox
	glBindVertexArray(m_vaoSky);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboSky);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); 

	std::cout << "Rendering " << m_meshSize << " points.\n";
	std::cout << "sizeof(Point): " << sizeof(Mesh) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// VAO setup plane
	glBindVertexArray(m_vaoPlane);

	// positons
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPlane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texcoords
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPlaneTex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeTexCoords), planeTexCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// n
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPlaneNrml);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeNormals), planeNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// depth fbo setup
	glGenFramebuffers(1, &m_fboShadowMap);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboShadowMap);

	glGenTextures(1, &m_shadowTex);
	glBindTexture(GL_TEXTURE_2D, m_shadowTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowTex, 0);
	

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete.\n";
	
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// scene g-buffer setup for ssao
	glGenFramebuffers(1, &m_fboScene);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboScene);

	glGenTextures(1, &m_gColorTex);
	glBindTexture(GL_TEXTURE_2D, m_gColorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_gColorTex, 0);

	glGenTextures(1, &m_gNormalTex);
	glBindTexture(GL_TEXTURE_2D, m_gNormalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_gNormalTex, 0);

	glGenTextures(1, &m_gPosTex);
	glBindTexture(GL_TEXTURE_2D, m_gPosTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_gPosTex, 0);

	glGenTextures(1, &m_gDepthTex);
	glBindTexture(GL_TEXTURE_2D, m_gDepthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_gDepthTex, 0);

	GLenum drawBuffers[] = {
	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1,
	GL_COLOR_ATTACHMENT2
	};

	glDrawBuffers(3, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "G-Buffer not complete.\n";

	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ssao fbo setup
	glGenFramebuffers(1, &m_fboSSAO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboSSAO);

	glGenTextures(1, &m_ssaoTex);
	glBindTexture(GL_TEXTURE_2D, m_ssaoTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ssaoTex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "SSAO Framebuffer not complete.\n";

	}

	m_ssaoPoints = generateRandomVecs();
	m_noiseValues = generateNoise();

	// blur fbo

	glGenFramebuffers(1, &m_fboBlur);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboBlur);

	glGenTextures(1, &m_ssaoBlurTex);
	glBindTexture(GL_TEXTURE_2D, m_ssaoBlurTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ssaoBlurTex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Blur Framebuffer not complete.\n";

	}


	glGenTextures(1, &m_noiseTex);
	glBindTexture(GL_TEXTURE_2D, m_noiseTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 4, 4, 0, GL_RG, GL_FLOAT, m_noiseValues.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::render(const float fps)
{
	

	glm::mat4 viewSkybox = glm::mat4(glm::mat3(m_pCamera->GetViewMatrix()));
	glm::mat4 projSkybox = glm::perspective(glm::radians(m_pCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 viewCamera = m_pCamera->GetViewMatrix();
	glm::mat4 projCamera = glm::perspective(glm::radians(m_pCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 modelCamera = glm::mat4(1.0f);

	glm::mat4 viewCameraInv = glm::inverse(viewCamera);

	// light mats
	glm::vec3 lightDir = dirLight->getDirection();
	glm::vec3 lightDirView = glm::normalize(glm::vec3(viewCamera * glm::vec4(lightDir, 0.0f)));
	glm::vec3 lightPos = -lightDir * 50.0f;

	// for shadowmap
	glm::mat4 lightView = glm::lookAt(lightPos,glm::vec3(0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightProj = glm::ortho(-30.0f, 30.0f,-30.0f, 30.0f, 1.0f, 100.0f); 

	// ------ Depth Pass for Shadowmapping (Light Perspective) ------

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboShadowMap);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader_depth->use();
	glUniformMatrix4fv(glGetUniformLocation(shader_depth->ID, "lightView"), 1, GL_FALSE, glm::value_ptr(lightView));
	glUniformMatrix4fv(glGetUniformLocation(shader_depth->ID, "lightProj"), 1, GL_FALSE, glm::value_ptr(lightProj));
	glUniformMatrix4fv(glGetUniformLocation(shader_depth->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelCamera));

	glBindVertexArray(m_vaoPlane);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glBindVertexArray(m_vaoObj);
	glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// ------ Scene Pass to FBO ------

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboScene);

	// skybox
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	glEnable(GL_DEPTH_TEST);

	shader_skybox->use();

	glUniformMatrix4fv(glGetUniformLocation(shader_skybox->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewSkybox));
	glUniformMatrix4fv(glGetUniformLocation(shader_skybox->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projSkybox));

	glBindVertexArray(m_vaoSky);

	m_skybox->bind_texture(0);
	glUniform1i(glGetUniformLocation(shader_skybox->ID, "skybox"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	// plane for ground

	glEnable(GL_DEPTH_TEST);
	
	shader_render->use();
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewCamera));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projCamera));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelCamera));

	glBindVertexArray(m_vaoPlane);

	textureGround->bind_texture(6);

	glUniform1i(glGetUniformLocation(shader_render->ID, "tex"), 6);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);

	// trailer rendering

	shader_render->use();

	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewCamera));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projCamera));
	glUniformMatrix4fv(glGetUniformLocation(shader_render->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelCamera));


	glBindVertexArray(m_vaoObj);

	texture->bind_texture(0);
	texture2->bind_texture(1);
	texture3->bind_texture(2);
	texture4->bind_texture(3);
	texture5->bind_texture(4);

	glUniform1i(glGetUniformLocation(shader_render->ID, "tex"), m_textureSlot);
	glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	
	// ------ SSAO ------
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboSSAO);
	glDisable(GL_DEPTH_TEST);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_noiseTex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gNormalTex);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gPosTex);

	shader_ssao_calc->use();

	glUniform1i(glGetUniformLocation(shader_ssao_calc->ID, "noiseTex"), 0);
	glUniform1i(glGetUniformLocation(shader_ssao_calc->ID, "normalTex"), 1);
	glUniform1i(glGetUniformLocation(shader_ssao_calc->ID, "posTex"), 2);
	glUniformMatrix4fv(glGetUniformLocation(shader_ssao_calc->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projCamera));
	glUniform1f(glGetUniformLocation(shader_ssao_calc->ID, "radius"), 0.5);
	glUniform1f(glGetUniformLocation(shader_ssao_calc->ID, "bias"), 0.025);
	glUniform2f(glGetUniformLocation(shader_ssao_calc->ID, "noiseScale"),  SCR_WIDTH / 4, SCR_HEIGHT/4);
	
	glUniform3fv(glGetUniformLocation(shader_ssao_calc->ID, "samples[0]"),static_cast<GLsizei>(m_ssaoPoints.size()),glm::value_ptr(m_ssaoPoints[0]));

	glBindVertexArray(m_vaoQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// ------ Blur Pass for SSAO ------

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboBlur);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ssaoTex);

	shader_ssao_blur->use();
	glUniform1i(glGetUniformLocation(shader_ssao_blur->ID, "ssaoTex"), 0);

	glBindVertexArray(m_vaoQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// ------ Final Render Pass to Screen ------
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ssaoBlurTex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gColorTex);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_gNormalTex);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_gPosTex);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_shadowTex);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, m_gDepthTex);

	shader_final->use();
	glUniform1i(glGetUniformLocation(shader_final->ID, "ssaoBlurTex"), 0);
	glUniform1i(glGetUniformLocation(shader_final->ID, "colorTex"), 1);
	glUniform3fv(glGetUniformLocation(shader_final->ID, "lightDir"), 1, glm::value_ptr(lightDirView));
	glUniform3fv(glGetUniformLocation(shader_final->ID, "color"), 1, glm::value_ptr(dirLight->getColor()));
	glUniform1f(glGetUniformLocation(shader_final->ID, "intensity"), dirLight->getIntensity());
	
	glUniformMatrix4fv(glGetUniformLocation(shader_final->ID, "invView"), 1, GL_FALSE, glm::value_ptr(viewCameraInv));
	glUniformMatrix4fv(glGetUniformLocation(shader_final->ID, "lightView"), 1, GL_FALSE, glm::value_ptr(lightView));
	glUniformMatrix4fv(glGetUniformLocation(shader_final->ID, "lightProj"), 1, GL_FALSE, glm::value_ptr(lightProj));

	glUniform1i(glGetUniformLocation(shader_final->ID, "normalTex"), 3);
	glUniform1i(glGetUniformLocation(shader_final->ID, "posTex"), 4);
	glUniform1i(glGetUniformLocation(shader_final->ID, "shadowTex"), 5);
	glUniform1i(glGetUniformLocation(shader_final->ID, "depthTex"), 6);

	glBindVertexArray(m_vaoQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void Renderer::RenderText(const float fps)
{

	std::vector<glm::vec3> m_ssaoKernel;

	glUseProgram(0);

	// debug text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCR_WIDTH, SCR_HEIGHT, 0, -1, 1);

	std::stringstream ss;
	ss << "FPS: " << fps << "\nTris: " << m_mesh.indices.size();
	std::string text = ss.str();

	static char buffer[99999];
	int num_quads = stb_easy_font_print(20, 20, (char*)text.c_str(), NULL, buffer, sizeof(buffer));

	glColor3f(1.0f, 1.0f, 0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

std::vector<glm::vec3> Renderer::generateRandomVecs(){
	std::vector <glm::vec3> randomVecs;
	std::mt19937 generator(1337);
	std::uniform_real_distribution<float> randomFloat(0.0f, 1.0f);

	for (int i = 0; i < 64; i++) {
		glm::vec3 randomVec(
			randomFloat(generator) * 2.0f - 1.0f,
			randomFloat(generator) * 2.0f - 1.0f,
			randomFloat(generator)
		);
		randomVec = glm::normalize(randomVec);
		randomVec *= randomFloat(generator);
		randomVecs.push_back(randomVec);
	}

	return randomVecs;
}

std::vector<glm::vec2> Renderer::generateNoise() {
	std::vector<glm::vec2> noise;
	std::mt19937 generator(1337);
	std::uniform_real_distribution<float> randomFloat(0.0f, 1.0f);
	for (int i = 0; i < 16; i++) {
		glm::vec2 randomVec(
			randomFloat(generator) * 2.0f - 1.0f,
			randomFloat(generator) * 2.0f - 1.0f
		);
		noise.push_back(randomVec);
	}
	return noise;
}
