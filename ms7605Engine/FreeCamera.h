#pragma once
#include "Camera.h"
#include "GameObject.h"
class FreeCamera : public Camera {
public:
	float speed;
	GLfloat pitch, yaw, roll, sensitivity;

	FreeCamera();
	FreeCamera(int width, int height);
	~FreeCamera();

	virtual void update();
	void process_movement(GLfloat xoff, GLfloat yoff);
	void process_mouse_scroll(GLfloat syoff);

};