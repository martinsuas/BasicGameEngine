#include "InputManager.h"
#include <iostream>
GLfloat InputManager::lastX = 0;
GLfloat InputManager::lastY = 0;
bool InputManager::firstMouse;
FreeCamera * InputManager::cam = NULL;

InputManager::InputManager() {}

InputManager::~InputManager() {}

std::map<int, bool> InputManager::keyDown;

void InputManager::keyCallback(GLFWwindow * windowPtr, int key,
	int scancode, int action, int mods) {
	keyDown[key] = action;
}

void InputManager::mouseClick(GLFWwindow * windowPtr, int button,
	int action, int mods) {
	keyDown[button] = action;
}

void InputManager::mouseCallback(GLFWwindow * windowPtr, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat xoff = xpos - lastX;
	GLfloat yoff = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	cam->process_movement(xoff, yoff);
}

void InputManager::scrollCallback(GLFWwindow * window, double sxoff, double syoff) {
	cam->process_mouse_scroll(syoff);
}


void InputManager::init(GLFWwindow* windowPtr, int width, int height, FreeCamera &camera) {
	glfwSetMouseButtonCallback(windowPtr, mouseClick);
	glfwSetKeyCallback(windowPtr, keyCallback);
	glfwSetCursorPosCallback(windowPtr, mouseCallback);
	glfwSetScrollCallback(windowPtr, scrollCallback);
	firstMouse = true;
	lastX = width / 2;
	lastY = height / 2;
	cam = &camera;
}

bool InputManager::press(int key) {
	return keyDown[key];
}
