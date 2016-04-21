#pragma once
// Extension manager, determine if the platform supports features and loads
// them at run time to access beyond OpenGL 1.2.
#include <GL/glew.h>
// Great for small program; makes programs more portable, handles windows
// creation and management, keyboard and mouse input, and a "game loop"
// GL_TRUE is 1 if it works, false 0 if it fails.
#include <GLFW/glfw3.h>
// Math library based on OpenGL Shading Language, making it easier to give values to
// shader variables and to buffer/upload data. Just library, hence .hpp
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/wrap.hpp>
#include <FreeImage.h>
#include <vector>
#include <memory>
#include <stdio.h>

// Engine
#include "ShaderManager.h"
#include "Input/InputManager.h"
#include "GameObject/Character2D.h"
#include "GameObject/Player.h"

class Engine {
private:
	// Creates windows with parameters given. Returns address of the GLFWwindow struct,
	// or nullptr if it fails to create it.
	GLFWwindow * GLFWwindowPtr;
	ShaderManager shader_manager;
	GLuint vertArr;
	GLuint vertBuf;
	GLuint texID;
	std::vector<unsigned int> vertNum;
	std::vector<std::shared_ptr<Character2D>> objects;
	//Player player;

	// Extras
	bool secondTexture;
	// Debug
	bool printOnce;


public:
	Engine();
	~Engine();
	bool init();
	bool bufferModel();
	bool addObject(std::shared_ptr<Character2D> obj);
	bool gameLoop();
	bool useShaders();
	void useTexture(char* texDir, bool wrap);
};