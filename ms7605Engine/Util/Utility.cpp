#include "Utility.h"
#include <glm/glm.hpp>

namespace Utility {
	void limit(glm::vec3 & vector, float limit) {
		if (glm::length(vector) > limit) {
			vector = glm::normalize(vector);
			vector.x *= limit;
			vector.y *= limit;
			vector.z *= limit;
		}
	}
}
