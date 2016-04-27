#pragma once
#include "GameObject/GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <memory>
class ObjectManager {
public:
	std::map<std::string, std::shared_ptr<GameObject>> objects;
	typedef std::map<std::string, std::shared_ptr<GameObject>>::iterator iter;

	bool addObject(std::string, std::shared_ptr<GameObject> obj);
	bool removeObject(std::string);
	void checkCollisions();

	GLuint vertArr;
	GLuint vertBuf;
};