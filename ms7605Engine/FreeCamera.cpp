#include "FreeCamera.h"
#include "InputManager.h"
#include <iostream>

FreeCamera::FreeCamera() {}

FreeCamera::~FreeCamera() {}

FreeCamera::FreeCamera(int w, int h) :
	Camera(w, h),
	speed(0.0005f),
	pitch(0.f),
	yaw(-90.f),
	roll(0.f),
	sensitivity(0.05f)
{}


void FreeCamera::update() {
	// Keyboard Movement
	if (InputManager::press(GLFW_KEY_W)) {
		eye += speed * lookat;
	}
	else if (InputManager::press(GLFW_KEY_A)) {
		eye -= glm::normalize(glm::cross(lookat, up)) * speed;
	}
	else if (InputManager::press(GLFW_KEY_S)) {
		eye -= speed * lookat;
	}
	else if (InputManager::press(GLFW_KEY_D)) {
		eye += glm::normalize(glm::cross(lookat, up)) * speed;
	}
	else if (InputManager::press(GLFW_KEY_E)) {
		eye += glm::normalize(glm::cross(right, lookat)) * speed;
	}
	else if (InputManager::press(GLFW_KEY_Q)) {
		eye -= glm::normalize(glm::cross(right, lookat)) * speed;
	}
	else {

	}

	view = glm::lookAt(eye, eye + lookat, up);

	float fovy = 3.14159f * .4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = 0.01f;
	float zFar = 1000.f;
	proj = glm::perspective(fovy, aspect, zNear, zFar);	
}

void FreeCamera::process_movement(GLfloat xoff, GLfloat yoff) {
	xoff *= sensitivity;
	yoff *= sensitivity;

	// Mouse Movement
	yaw += xoff;
	pitch += yoff;

	if (pitch > 180.f)
		pitch = 180.f;
	if (pitch < -180.f)
		pitch = -180.f;

	vec3 cameraFront;
	cameraFront.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	cameraFront.y = glm::sin(glm::radians(pitch));
	cameraFront.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
	lookat = glm::normalize(cameraFront);
	right = glm::normalize(glm::cross(lookat, world_up));
	up = glm::normalize(glm::cross(right, lookat));
}

void FreeCamera::process_mouse_scroll(GLfloat syoff) {
	// Mouse scroll zoom
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom += syoff;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}