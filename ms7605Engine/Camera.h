#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using glm::vec3;
class Camera {
public:
	bool ortho, frustum;
	// Camera
	vec3 eye, lookat, up, right, world_up, direction;
	glm::mat4 view, proj;
	float zoom;
	int width, height;

	Camera();
	Camera(int width, int height);

	virtual void update();
	void set_camera(vec3 eye, vec3 lookat, vec3 up);
	void is_ortho(bool b);
	void is_frustum(bool b);
	glm::mat4 get_view();
	glm::mat4 get_proj();
};

inline void Camera::is_ortho(bool b) { ortho = b; }
inline void Camera::is_frustum(bool b) { frustum = b; }