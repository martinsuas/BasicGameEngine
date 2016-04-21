#include "GameObject.h"
using glm::vec3;
#include <iostream>

GameObject::GameObject() :
	loc(vec3(0.0f)),
	velocity(vec3(0.0f)),
	acceleration(vec3(0.0f)),
	forward(vec3(0.0f)),
	//right(vec3(0.0f)),
	dim(vec3(0.5f, 0.5f, 0.5f)),
	mass(1.0f),
	max_speed(1.0f),
	max_force(2.0f),
	behavior(STILL)
{}

GameObject::GameObject(vec3 loc, vec3 rot, vec3 dim) :
	loc(loc),
	rot(rot),
	dim(dim),
	velocity(vec3(0.0f)),
	acceleration(vec3(0.0f)),
	mass(1.0f),
	forward(glm::normalize(velocity)),
	//right(vec3(forward.z, forward.y, -forward.x)),
	max_speed(1.0f),
	max_force(2.0f),
	behavior(STILL)
{}


GameObject::~GameObject() {}

void GameObject::update() {
	calculateSteeringForces();
	velocity += acceleration;
	Utility::limit(velocity, max_speed);
	loc += velocity;
	forward = glm::normalize(velocity);
	//right(vec3(-forward.z, forward.y, -forward.x));
	acceleration *= 0;
}

void GameObject::applyForce(const vec3 force) {
	acceleration += (force / mass);
}

void GameObject::deaccelerate() {
	if (glm::length(velocity) > 1)
		velocity *= 0.1;
	else
		velocity *= 0;
}

vec3 GameObject::steer(GameObject::SteeringBehavior bh, vec3 target) {
	if (bh == SEEK) {
		vec3 desired = glm::normalize(target - loc) * max_speed;
		vec3 steer = desired - velocity;
		Utility::limit(steer, max_force);
		return steer;
	}
	else if (bh == PLAYER) {
		return vec3(0);
	}
	else { // STILL
		deaccelerate();
		return vec3(0);
	}
}

//void GameObject::calculateSteeringForces() { }