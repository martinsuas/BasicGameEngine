#include "Utility.h"
#include <glm/glm.hpp>
#include <iostream>
namespace Utility {
	void limit(glm::vec3 & vector, float limit) {
		if (glm::length(vector) > limit) {
			vector = glm::normalize(vector);
			vector.x *= limit;
			vector.y *= limit;
			vector.z *= limit;
		}
	}
	void print4Matrix(const glm::mat4 &mat) {
		for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					std::cout << mat[i][j] << " ";
				}
			std::cout << std::endl;
		}
	}
}
