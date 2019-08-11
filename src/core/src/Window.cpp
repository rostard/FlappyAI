//
// Created by rostard on 11.12.17.
//

#include <iostream>
#include "Window.h"
#include "Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* Window::window = nullptr;
bool Window::initialized = false;

void Window::createWindow(const unsigned int screen_width, const unsigned int screen_height, const std::string& title) {

    window = glfwCreateWindow(screen_width, screen_height, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (window == nullptr)
    {
        glfwTerminate();
        Log::Message(std::string("Failed to create GLFW window"), LOG_ERROR);
    }

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

bool Window::isShouldClose() {
    return static_cast<bool>(glfwWindowShouldClose(window));
}

void Window::render() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::getKey(const int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::getMouseButton(const int button) {
    return static_cast<bool>(glfwGetMouseButton(window, button));
}

void Window::dispose() {
    glfwDestroyWindow(window);
    glfwTerminate();

}

void Window::initGLFW() {
    if(initialized)
        return;
    initialized = true;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
