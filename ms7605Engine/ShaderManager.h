#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class ShaderManager {
private:
	GLuint program;  // Index where the loaded shaders are stored on the
					 // graphics class.
public:
	ShaderManager();
	~ShaderManager();

	GLuint getProgram() const;
	/*Load shaders. Returns 0 if it succeeds, any other number if it fails.*/
	bool loadShaders(const char* vertexFile, const char* fragmentFile);
	/*Used by loadShaders to read and compile a shader file and return
	index where it is stored.*/
	GLuint loadShader(const char* file, GLenum shaderType);
};