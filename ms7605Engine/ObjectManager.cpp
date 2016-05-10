#include "ObjectManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

bool ObjectManager::addObject(std::string key, std::shared_ptr<GameObject> obj) {
	objects.insert(std::pair<std::string, std::shared_ptr<GameObject>>(key, obj));
	return true;
}

void ObjectManager::checkCollisions() {
	bool hero_hit = false;
	for (iter it1 = objects.begin(); it1 != objects.end(); it1++) {
		for (iter it2 = objects.begin(); it2 != objects.end(); it2++) {
			if (it1 != it2) {
				GameObject *A = objects.at(it1->first).get();
				GameObject *B = objects.at(it2->first).get();
				if (A->label == GameObject::PLAYER && B->label == GameObject::ENEMY) {
					if (A->collides(B))
						hero_hit = true;
				}
			}
		}
	}
	if (hero_hit) {
		objects.at("ouch")->set_invisibility(false);
		objects.at("ouch")->set_loc(objects.at("thief")->loc);
		objects.at("ouch")->loc.y += 1.0;
	}
	else {
		objects.at("ouch")->set_invisibility(true);
	}
}