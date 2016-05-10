#include "FollowingCamera.h"
#include "InputManager.h"
#include <iostream>

FollowingCamera::FollowingCamera() {}

FollowingCamera::~FollowingCamera() {}

FollowingCamera::FollowingCamera(int w, int h) :
	Camera(w, h),
	target(NULL),
	offset(1.0f),
	theta(0.f),
	phi(0.0f)
{}


void FollowingCamera::update() {

	if (target != NULL) {
		eye = target->loc;
		lookat = target->loc;

		if (InputManager::press(GLFW_KEY_U)) {
			phi += 0.0005;
		}
		else if (InputManager::press(GLFW_KEY_J)) {
			phi -= 0.0005;
		}
		else if (InputManager::press(GLFW_KEY_H)) {
			theta -= 0.0005;
		}
		else if (InputManager::press(GLFW_KEY_K)) {
			theta += 0.0005;
		}
		else if (InputManager::press(GLFW_KEY_P)) {
			offset += 0.0005;
		}
		else if (InputManager::press(GLFW_KEY_O)) {
			offset -= 0.0005;
		}
		else {

		}
		float x = offset * glm::sin(theta) * glm::cos(phi);
		float y = offset * glm::sin(theta) * glm::sin(phi);
		float z = offset * glm::cos(theta);
		eye += vec3(x, y, z);
		std::cout << phi << " " << theta << std::endl;
	}
	else {
		std::cout << "null";
	}
	Camera::update();
}