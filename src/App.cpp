#include "App.h"

App::App(unsigned int width, unsigned height)
{

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}
	window = glfwCreateWindow(width, height, "Depth Buffer Normal Calculation", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}

	camera = new Camera(glm::vec3(0.0f, 2.0f, 12.0f));
	renderer = new Renderer(camera);
	renderer->start();


}

App::~App() {
	delete renderer;
	delete camera;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::run() {

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		renderer->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void App::processInput(GLFWwindow* window)
{
	// movement

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->ProcessKeyboard(ROTATE_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->ProcessKeyboard(ROTATE_RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (!up_key_pressed) {
			up_key_pressed = true;
			renderer->switchTexture(true);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
		up_key_pressed = false;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (!down_key_pressed) {
			down_key_pressed = true;
			renderer->switchTexture(false);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		down_key_pressed = false;
	}

}



void App::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	/*
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
	*/
}