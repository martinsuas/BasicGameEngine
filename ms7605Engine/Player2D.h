#pragma once
#include "Object2D.h"
#include "InputManager.h"

class Player2D : public Object2D {
public:
	//InputManager im;
	float max_acceleration;

	Player2D();
	Player2D(char* texDir, vec3 loc, vec3 rot, vec3 dim);
	~Player2D();

	virtual void calculateSteeringForces();
	void set_max_acceleration(const float a);
	//Camera get_camera();
};

inline void Player2D::set_max_acceleration(const float a) {
	max_acceleration = a;
}
