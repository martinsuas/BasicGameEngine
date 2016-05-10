#include "ShaderManager.h"
#include <fstream>
#include <iostream>
#include <ios>

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

GLuint ShaderManager::getProgram() const {
	return program;
}

/*Load shaders. Returns 0 if it succeeds, any other number if it fails.*/
bool ShaderManager::loadShaders(const char* vertexFile, const char* fragmentFile) {
	GLuint v, f;
	try {
		v = loadShader(vertexFile, GL_VERTEX_SHADER);
		f = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	}
	catch (...) {
		std::cout << "Load shader failed!";
		return false;
	}

	program = glCreateProgram();
	// Returns index of a single, linked program
	glAttachShader(program, v);
	glAttachShader(program, f);
	glLinkProgram(program);

	GLint result;
	try {
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		return true;
	}
	catch (...) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &result);
		GLchar* log = new char[result];
		glGetProgramInfoLog(program, result, 0, log);
		//log[result] = 0;
		std::cout << log;
		delete[] log;
		return false;
	}
}

/*Used by loadShaders to read and compile a shader file and return
index where it is stored.*/
GLuint ShaderManager::loadShader(const char* file, GLenum shaderType) {
	std::ifstream i;
	i.open(file, std::ios::binary);
	// If cannot be opened, return error
	if (!i.is_open()) { return 0; }
	// Get length and load string
	i.seekg(0, std::ios::end);
	GLuint length = (int)i.tellg();
	i.seekg(0, std::ios::beg);
	char* contents = new char[length + 1];
	i.read(contents, length);
	contents[length] = 0;
	i.close();

	// Create, Set, and Compile the shader
	GLuint index = glCreateShader(shaderType);
	// ^ Returns index of shader object
	glShaderSource(index, 1, (const char**)&contents, 0);
	// Set the source code:
	//  1. Index
	//  2. How many string make up the code
	//  3. A pointer to the character array where code is loaded
	//  4. Array of string sizes - 0 means string are null terminated
	glCompileShader(index);
	// May or may not succeed
	// Use glGetShaderiv( index, info, address of GLint)
	// 1. index of shader
	// 2. Which info to get? In this case, GL_COMPILE_STATUS
	// 3. 0 is failure
	delete[] contents;
	GLint result;

	try {
		glGetShaderiv(index, GL_COMPILE_STATUS, &result);
		return index;
	}
	catch (...) {
		glGetShaderiv(index, GL_INFO_LOG_LENGTH, &result);
		GLchar* log = new char[result];
		glGetShaderInfoLog(index, result, 0, log);
		std::cout << log;
		delete[] log;
		return 0;
	}
}