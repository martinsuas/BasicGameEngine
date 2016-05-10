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
#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
#include <ctime>

// Engine
#include "ShaderManager.h"
#include "InputManager.h"
#include "Model.h"
// GameObjects
#include "Object2D.h"
#include "Player2D.h"
#include "ObjectManager.h"
// Cameras
#include "Camera.h"
#include "FollowingCamera.h"
#include "FreeCamera.h"

class Engine {
private:
	// Creates windows with parameters given. Returns address of the GLFWwindow struct,
	// or nullptr if it fails to create it.
	GLFWwindow * GLFWwindowPtr;
	// Create and binds shaders
	ShaderManager shader_manager;
	// Create and manages objects
	ObjectManager om;
	// Default view
	FreeCamera camera;
	
	//std::vector<unsigned int> vertNum;
	typedef std::map<std::string, std::shared_ptr<GameObject>>::iterator iter;
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
	bool gameLoop();
	bool useShaders();
	GLuint useTexture(char* texDir, bool wrap);
};