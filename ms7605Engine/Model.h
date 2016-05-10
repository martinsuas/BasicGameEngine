#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "GameObject.h"
using glm::vec3;
using glm::vec2;


class Model {	
public:
	GLuint vertArr;
	GLuint vertBuf;
	unsigned int vertCount;
	GLuint texture;
	GameObject* go;

	Model();
	~Model();

	bool buffer(std::string objfile);
	bool render();
	void set_texture(GLuint texture);
	void set_game_object_ptr(GameObject* go);
};

inline void Model::set_texture(GLuint _texture) {
	texture = _texture;
}

inline void Model::set_game_object_ptr(GameObject* _go) {
	go = _go;
}