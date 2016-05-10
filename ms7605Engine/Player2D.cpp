#include "Player2D.h"
#include <iostream>

Player2D::Player2D() :
	max_acceleration(0.5f)
{}

Player2D::Player2D(char* texDir, vec3 loc, vec3 rot, vec3 dim) :
	Object2D(texDir, loc, rot, dim),
	max_acceleration(0.5f)
	{}

Player2D::~Player2D() {}

void Player2D::calculateSteeringForces() {
	vec3 steering_force;
	if (InputManager::press(GLFW_KEY_LEFT)) {
		behavior = SEEK;
		flip = true;
		steering_force = steer(behavior, loc - vec3(max_acceleration, 0, 0));
	}
	else if (InputManager::press(GLFW_KEY_RIGHT)) {
		behavior = SEEK;
		flip = false;
		steering_force = steer(behavior, loc + vec3(max_acceleration, 0, 0));
	}
	else if (InputManager::press(GLFW_KEY_UP)) {
		behavior = SEEK;
		steering_force = steer(behavior, loc + vec3(0, max_acceleration, 0));
	}
	else if (InputManager::press(GLFW_KEY_DOWN)) {
		behavior = SEEK;
		steering_force = steer(behavior, loc - vec3(0, max_acceleration, 0));
	}
	else {
		behavior = STILL;
		steer(behavior);
	}
	applyForce(steering_force);
}