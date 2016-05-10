#pragma once
#include "Camera.h"
#include "GameObject.h"
class FollowingCamera : public Camera {
public:
	float offset;
	std::shared_ptr<GameObject> target;
	float theta, phi;

	FollowingCamera();
	FollowingCamera(int width, int height);
	~FollowingCamera();

	void set_target(std::shared_ptr<GameObject> target);
	void set_offset(float offset);
	virtual void update();
};
inline void FollowingCamera::set_target(std::shared_ptr<GameObject> _target) {
	target = _target;
}

inline void FollowingCamera::set_offset(float _offset) {
	offset = _offset;
}