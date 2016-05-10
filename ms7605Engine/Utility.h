#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
namespace Utility {
	void limit(glm::vec3 &vector, float limit);
	void print4Matrix(const glm::mat4 &mat);
}