#include "Player.h"
#include <iostream>

Player::Player() :
	max_acceleration(0.5f)
{}

Player::Player(char* texDir, vec3 loc, vec3 rot, vec3 dim) :
	Character2D(texDir, loc, rot, dim),
	max_acceleration(0.5f)
	{}

Player::~Player() {}

void Player::calculateSteeringForces() {
	vec3 steering_force;
	if (InputManager::press(GLFW_KEY_A)) {
		behavior = SEEK;
		steering_force = steer(behavior, loc - vec3(max_acceleration, 0, 0));
	}
	else if (InputManager::press(GLFW_KEY_D)) {
		behavior = SEEK;
		steering_force = steer(behavior, loc + vec3(max_acceleration, 0, 0));
	}
	else {
		behavior = STILL;
		steer(behavior);
	}
	applyForce(steering_force);
}