#pragma once
#include "GameObject.h"
//using glm::vec2;
class Character2D : public GameObject {
public:
	Character2D();
	Character2D(char* texDir);
	Character2D(char* texDir, vec3 loc, vec3 rot, vec3 dim);
	~Character2D();

	virtual void calculateSteeringForces();
	void set_target(const vec3 &target);
	void set_texture(char* tex);
	void forget_target();
	void toggle_wrap();

//protected:
	char* texDir;
	vec3 target;
	bool has_target, wrap;
};

inline void Character2D::set_target(const vec3 &_target) {
	target = _target;
	has_target = true;
}

inline void Character2D::set_texture(char* text) {
	texDir = text;
}

inline void Character2D::forget_target() {
	has_target = false;
}

inline void Character2D::toggle_wrap() {
	wrap = !wrap;
}