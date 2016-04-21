#include "InputManager.h"

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

void InputManager::init(GLFWwindow* windowPtr) {
	glfwSetMouseButtonCallback(windowPtr, mouseClick);
	glfwSetKeyCallback(windowPtr, keyCallback);
}

bool InputManager::press(int key) {
	return keyDown[key];
}
