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
	time_d(1.0f),
	invisible(false),
	bound(BOUNDLESS),
	label(BACKGROUND),
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
	time_d(1.0f),
	invisible(false),
	bound(BOUNDLESS),
	label(BACKGROUND),
	behavior(STILL)
{}


GameObject::~GameObject() {}

void GameObject::update() {
	calculateSteeringForces();
	vec3 velocity_d = acceleration * time_d;
	velocity += velocity_d;
	Utility::limit(velocity, max_speed);
	vec3 loc_d = velocity * time_d;
	loc += loc_d;
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
	else if (bh == CONTROLLED) {
		return vec3(0);
	}
	else { // STILL
		deaccelerate();
		return vec3(0);
	}
}

bool GameObject::collides(GameObject * B) {
	if (bound == SQUARE && B->bound == SQUARE) {
		if (loc.x < (B->loc.x + B->dim.x) &&
			(loc.x + dim.x) > B->loc.x &&
			loc.y < (B->loc.y + B->dim.y) &&
			(loc.y + dim.y) > B->loc.y &&
			loc.z < (B->loc.z + B->dim.z) &&
			(loc.z + dim.z) > B->loc.z){
			return true;
		}
	}
	if (bound == SPHERE && B->bound == SPHERE) {
		float r1, r2;
		r1 = dim.x / 2;
		r2 = B->dim.x / 2;
		if (r1 + r2 > glm::distance(loc, B->loc))
			return true;
	}

	//if (bound == SQUARE && B->bound == SPHERE) {

	//}
	return false;
}