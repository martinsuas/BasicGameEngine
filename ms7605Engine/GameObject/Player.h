#pragma once
#include "Character2D.h"
#include "../Input/InputManager.h"
class Player : public Character2D {
public:
	//InputManager im;
	float max_acceleration;

	Player();
	Player(char* texDir, vec3 loc, vec3 rot, vec3 dim);
	~Player();

	virtual void calculateSteeringForces();
	void set_max_acceleration(const float a);
};

inline void Player::set_max_acceleration(const float a) {
	max_acceleration = a;
}