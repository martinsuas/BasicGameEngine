#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Utility.h"
#include <memory>
#include <string>
using glm::vec3;

class GameObject {
public:
	enum SteeringBehavior { STILL, SEEK, CONTROLLED };
	enum Label { PLAYER, BACKGROUND, ENEMY };
	enum Bound { SQUARE, SPHERE, BOUNDLESS};
	
	GameObject(vec3 loc, vec3 rot, vec3 dim);
	GameObject();
	~GameObject();

	vec3 steer(SteeringBehavior bh, vec3 target = vec3());

	void update();
	virtual void calculateSteeringForces() = 0;
	void applyForce(const vec3 force);
	void deaccelerate();
	bool collides(GameObject* go);
	bool buffer(std::string objfile);
	bool buffer();
	bool render();

	// Vectors and Physics
	vec3 loc, rot, dim, velocity, acceleration, forward;// , right;
	glm::mat4 owm; // object world matrix
	float mass, max_speed, max_force, time_d;

	void set_loc(const vec3 loc);
	void set_rot(const vec3 rot);
	void set_dim(const vec3 dim);
	void set_velocity(const vec3 velocity);
	void set_acceleration(const vec3 acceleration);
	void set_mass(const float mass);
	void set_max_speed(const float speed);
	void set_max_force(const float force);
	void set_time_d(float time_d);

	// Classification
	SteeringBehavior behavior;
	Label label;
	Bound bound;
	std::shared_ptr<GameObject> target;
	bool has_target;

	void set_behavior(SteeringBehavior bh);
	void set_label(Label label);
	void set_bound(Bound bound);
	void set_target(std::shared_ptr<GameObject> go);
	void forget_target();

	// Textures
	GLuint texture;
	char* texDir;
	bool  wrap, invisible, flip;

	void set_texture(GLuint texture);
	void set_texture_dir(char* texdir);
	void toggle_wrap();
	void set_invisibility(const bool invisibility);
	void set_flip(const bool flip);
	

	// Object files and object's vertices
	GLuint vertArr;
	GLuint vertBuf;
	unsigned int vertCount;
	//std::string objfile;

	//void set_objfile(std::string objfile);
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

inline void GameObject::set_bound(const Bound _bound) {
	bound = _bound;
}


inline void GameObject::set_target(std::shared_ptr<GameObject> go) {
	target = go;
	has_target = true;
}

inline void GameObject::set_texture_dir(char* textdir) {
	texDir = textdir;
}


inline void GameObject::forget_target() {
	has_target = false;
}

inline void GameObject::toggle_wrap() {
	wrap = !wrap;
}

inline void GameObject::set_time_d(float _time_d) {
	time_d = _time_d;
}

inline void GameObject::set_label(const Label _label) {
	label = _label;
}

inline void GameObject::set_invisibility(const bool _invisible) {
	invisible = _invisible;
}

inline void GameObject::set_flip(const bool _flip) {
	flip = _flip;
}

inline void GameObject::set_texture(GLuint _texture) {
	texture = _texture;
}

//inline void GameObject::set_objfile(std::string _objfile) {
	//objfile = _objfile;
//}
