#include "Object2D.h"
#include <iostream>

Object2D::Object2D() {}

Object2D::Object2D(char* _texDir) :
	GameObject() {
	texDir = _texDir;
	has_target = false;
}
Object2D::Object2D(char* _texDir, vec3 _loc, vec3 _rot, vec3 _dim) :
	GameObject(_loc, _rot, _dim) {
	texDir = _texDir;
	has_target = false;
}

Object2D::~Object2D() {
}

void Object2D::calculateSteeringForces() {
	//if (has_target) {
		//vec3 steering_force = steer(behavior, target->loc);
		//acceleration += (steering_force / mass);	
	//}
}