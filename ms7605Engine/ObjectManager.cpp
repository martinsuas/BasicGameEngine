#include "ObjectManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

bool ObjectManager::addObject(std::string key, std::shared_ptr<GameObject> obj) {
	objects.insert(std::pair<std::string, std::shared_ptr<GameObject>>(key, obj));

	std::vector<glm::vec3> locs = {
		{ 0., 1., 0 }, //0
		{ 0., 0., 0.0 }, //1 - 1
		{ 1., 0., 0.0 }, //2 - 2
		{ 1., 1., 0.0 } //3 - 3
	};

	// Define location data for a star
	std::vector<unsigned int> locInds = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int vertCount = locInds.size();
	obj->set_vert_num(vertCount);
	//vertNum.push_back(vertCount);
	// Duplicate data into single buffer for easier processing
	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
		vertBufData[i] = locs[locInds[i]];

	// Generate vertex array and buffer (int size (# of arrays), GLuint *arrays)
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// Bind buffers
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// Store data in buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertCount,
		&vertBufData[0], GL_STATIC_DRAW);

	// Describe data to buffer
	glEnableVertexAttribArray(0); // enable a vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Prepare window and data info
	glClearColor(0.1f, 0.1f, 0.5f, 0.5f); // Sets display-window color to white.
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
		objects.at("ouch")->loc.y += 0.6;
	}
	else {
		objects.at("ouch")->set_invisibility(true);
	}
}