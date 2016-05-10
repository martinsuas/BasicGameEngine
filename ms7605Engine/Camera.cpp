#include "Camera.h"
#include <iostream>

Camera::Camera() {}

Camera::Camera(int width, int height) :
	width(width),
	height(height),
	zoom(1.f),
	eye(vec3()),
	lookat(vec3()),
	up(vec3()),
	ortho(false),
	frustum(false)
	{}

void Camera::set_camera(vec3 _eye, vec3 _lookat, vec3 _up) {
	eye = _eye;
	lookat = _lookat;
	up = _up;
	direction = glm::normalize(eye - lookat);
	right = glm::normalize(glm::cross(up, direction));
	world_up = glm::cross(direction, right);
}
	
glm::mat4 Camera::get_view() {
	update();
	return view; 
}
glm::mat4 Camera::get_proj() {
	update();
	return proj; 
}

void Camera::update() {
	view = glm::lookAt(eye, lookat, up);//eye + direction, up);
	float fovy = 3.14159f * .4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = 0.01f;
	float zFar = 1000.f;
	proj = glm::perspective(fovy, aspect, zNear, zFar);
}