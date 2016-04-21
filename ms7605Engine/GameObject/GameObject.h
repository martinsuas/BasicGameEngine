#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../Util/Utility.h"
using glm::vec3;

class GameObject {
public:
	enum SteeringBehavior { STILL, SEEK, PLAYER };
	GameObject();
	GameObject(vec3 loc, vec3 rot, vec3 dim);
	~GameObject( );

	vec3 steer(SteeringBehavior bh, vec3 target = vec3());

	void update();
	virtual void calculateSteeringForces() = 0;
	void applyForce(const vec3 force);
	void deaccelerate();

	void set_loc(const vec3 loc);
	void set_rot(const vec3 rot);
	void set_dim(const vec3 dim);
	void set_velocity(const vec3 velocity);
	void set_acceleration(const vec3 acceleration);
	void set_mass(const float mass);
	void set_max_speed(const float speed);
	void set_max_force(const float force);
	void set_behavior(SteeringBehavior bh);

//protected:
	vec3 loc, rot, dim, velocity, acceleration, forward;// , right;
	glm::mat4 owm; // object world matrix
	float mass, max_speed, max_force;
	SteeringBehavior behavior;
};

inline void GameObject::set_loc(const vec3 _loc) {
	loc = _loc;
}

inline void GameObject::set_rot(const vec3 _rot) {
	rot = _rot;
}

inline void GameObject::set_dim(const vec3 _dim) {
	dim = _dim;
}

inline void GameObject::set_velocity(const vec3 _velocity) {
	velocity = _velocity;
}

inline void GameObject::set_acceleration(const vec3 _acceleration) {
	acceleration = _acceleration;
}

inline void GameObject::set_mass(const float _mass) {
	mass = _mass;
}

inline void GameObject::set_max_speed(const float _max_speed) {
	max_speed = _max_speed;
}

inline void GameObject::set_max_force(const float _max_force) {
	max_force = _max_force;
}

inline void GameObject::set_behavior(const SteeringBehavior _behavior) {
	behavior = _behavior;
}