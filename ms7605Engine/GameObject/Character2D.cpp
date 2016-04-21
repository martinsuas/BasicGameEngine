#include "Character2D.h"
#include <iostream>

Character2D::Character2D() {}

Character2D::Character2D(char* _texDir) :
	GameObject() {
	texDir = _texDir;
	has_target = false;
}
Character2D::Character2D(char* _texDir, vec3 _loc, vec3 _rot, vec3 _dim) :
	GameObject(_loc, _rot, _dim) {
	texDir = _texDir;
	has_target = false;
}

Character2D::~Character2D() {
}

void Character2D::calculateSteeringForces() {
	if (texDir == "Images/thief.png lala") {
		std::cout << loc.x << " " << loc.y << " " << loc.z << std::endl
			<< velocity.x << " " << velocity.y << " " << velocity.z << std::endl 
			<< std::endl;
	}
	if (has_target) {
		vec3 steering_force = steer(behavior, target);
		//std::cout << "f" << steering_force.x << " " << steering_force.y << " "
			//<< steering_force.z << std::endl << std::endl;
		acceleration += (steering_force / mass);	
	}
}