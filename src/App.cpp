#include "App.h"

App::App(unsigned int width, unsigned int height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    // Create window
    window = glfwCreateWindow(width, height, "Mesh Renderer", nullptr, nullptr);
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

        float fps = 1.0f / deltaTime;
        renderer->render(fps);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::processInput(GLFWwindow* window) {
    // move
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

    // texture switch
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !up_key_pressed) {
        up_key_pressed = true;
        renderer->switchTexture(true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
        up_key_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !down_key_pressed) {
        down_key_pressed = true;
        renderer->switchTexture(false);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
        down_key_pressed = false;
    }

    // light rotation
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        renderer->rotateLight(true);
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        renderer->rotateLight(false);

    bool shiftPressed =
        glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    bool leftMousePressed =
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    if (shiftPressed && leftMousePressed) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (light_drag_active) {
            renderer->rotateLightMouse(
                static_cast<float>(mouseX - last_light_mouse_x),
                static_cast<float>(mouseY - last_light_mouse_y)
            );
        }

        last_light_mouse_x = mouseX;
        last_light_mouse_y = mouseY;
        light_drag_active = true;
    }
    else {
        light_drag_active = false;
    }
}

void App::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    // Mouse callback currently disabled
    /*
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
    */
}
