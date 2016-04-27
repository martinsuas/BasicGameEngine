#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

//using glm::vec2;
class Object2D : public GameObject {
public:
	Object2D();
	Object2D(char* texDir);
	Object2D(char* texDir, vec3 loc, vec3 rot, vec3 dim);
	~Object2D();

	virtual void calculateSteeringForces();
//protected:
};
