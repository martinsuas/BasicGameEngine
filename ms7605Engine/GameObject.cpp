#include "GameObject.h"
using glm::vec3;
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

GameObject::GameObject() :
	loc(vec3(0.0f)),
	velocity(vec3(0.0f)),
	acceleration(vec3(0.0f)),
	forward(vec3(0.0f)),
	//right(vec3(0.0f)),
	dim(vec3(0.5f, 0.5f, 0.5f)),
	mass(1.0f),
	max_speed(1.0f),
	max_force(2.0f),
	time_d(1.0f),
	invisible(false),
	bound(BOUNDLESS),
	label(BACKGROUND),
	behavior(STILL)
{}

GameObject::GameObject(vec3 loc, vec3 rot, vec3 dim) :
	loc(loc),
	rot(rot),
	dim(dim),
	velocity(vec3(0.0f)),
	acceleration(vec3(0.0f)),
	mass(1.0f),
	forward(glm::normalize(velocity)),
	//right(vec3(forward.z, forward.y, -forward.x)),
	max_speed(1.0f),
	max_force(2.0f),
	time_d(1.0f),
	invisible(false),
	bound(BOUNDLESS),
	label(BACKGROUND),
	behavior(STILL)
{}


GameObject::~GameObject() {}

void GameObject::update() {
	calculateSteeringForces();
	vec3 velocity_d = acceleration * time_d;
	velocity += velocity_d;
	Utility::limit(velocity, max_speed);
	vec3 loc_d = velocity * time_d;
	loc += loc_d;
	forward = glm::normalize(velocity);
	//right(vec3(-forward.z, forward.y, -forward.x));
	acceleration *= 0;
}

void GameObject::applyForce(const vec3 force) {
	acceleration += (force / mass);
}

void GameObject::deaccelerate() {
	if (glm::length(velocity) > 1)
		velocity *= 0.1;
	else
		velocity *= 0;
}

vec3 GameObject::steer(GameObject::SteeringBehavior bh, vec3 target) {
	if (bh == SEEK) {
		vec3 desired = glm::normalize(target - loc) * max_speed;
		vec3 steer = desired - velocity;
		Utility::limit(steer, max_force);
		return steer;
	}
	else if (bh == CONTROLLED) {
		return vec3(0);
	}
	else { // STILL
		deaccelerate();
		return vec3(0);
	}
}

bool GameObject::collides(GameObject * B) {
	if (bound == SQUARE && B->bound == SQUARE) {
		if (loc.x < (B->loc.x + B->dim.x) &&
			(loc.x + dim.x) > B->loc.x &&
			loc.y < (B->loc.y + B->dim.y) &&
			(loc.y + dim.y) > B->loc.y &&
			loc.z < (B->loc.z + B->dim.z) &&
			(loc.z + dim.z) > B->loc.z){
			return true;
		}
	}
	if (bound == SPHERE && B->bound == SPHERE) {
		float r1, r2;
		r1 = dim.x / 2;
		r2 = B->dim.x / 2;
		if (r1 + r2 > glm::distance(loc, B->loc))
			return true;
	}

	//if (bound == SQUARE && B->bound == SPHERE) {

	//}
	return false;
}

bool GameObject::buffer(std::string objfile) {
	std::ifstream file;
	file.open(objfile);
	std::string line;
	int num_elements;
	int locN = 0, texN = 0, norN = 0, facN = 0;
	int locT = 0, texT = 0, norT = 0, facT = 0;
	std::vector<GLfloat> locs;
	std::vector<GLfloat> texs;
	std::vector<GLfloat> nors;
	std::vector<GLfloat> vertBufData;

	bool pLoc = false, pTex = false, pNor = false;

	while (getline(file, line)) {
		num_elements = 0;
		std::istringstream iss(line);
		std::string command;
		iss >> command;
		if (command.compare("v") == 0) {
			locT++;
			while (iss >> command) {
				num_elements++;
				locs.push_back(std::stof(command));
			}
			if (locN == 0)
				locN = num_elements;
		}
		else if (command.compare("vt") == 0) {
			// Debug
			if (pLoc) {
				for (int i = 0; i < locT*locN; i++) {
					if (i % locN == 0)
						std::cout << std::endl;
					std::cout << locs[i] << " ";
				}
				std::cout << std::endl << "locT: " << locT << std::endl;
				pLoc = false;
			}
			// end debug
			texT++;
			while (iss >> command) {
				num_elements++;
				texs.push_back(std::stof(command));
			}
			if (texN == 0)
				texN = num_elements;
		}
		else if (command.compare("vn") == 0) {
			// Debug
			if (pTex) {
				for (int i = 0; i < texT*texN; i++) {
					if (i % texN == 0)
						std::cout << std::endl;
					std::cout << texs[i] << " ";
				}
				std::cout << std::endl << "texT: " << texT << std::endl;
				pTex = false;
			}
			// end debug
			norT++;
			while (iss >> command) {
				num_elements++;
				nors.push_back(std::stof(command));
			}
			if (norN == 0)
				norN = num_elements;
		}
		else if (command.compare("f") == 0) {
			// Debug
			if (pNor) {
				for (int i = 0; i < norT*norN; i++) {
					if (i % norN == 0)
						std::cout << std::endl;
					std::cout << nors[i] << " ";
				}
				std::cout << std::endl << "norT: " << norT << std::endl;
				pNor = false;
			}
			// end debug
			while (iss >> command) {
				std::vector<int> elems;
				std::stringstream ss(command);
				std::string item;
				int i = 0;
				while (std::getline(ss, item, '/')) {
					elems.push_back(std::stoi(item));
					i++;
				}

				//std::cout << elems.at(0) << " " << elems.at(1) << " " << elems.at(2)  << std::endl;

				if (i >= 1) {
					for (int j = 0; j < locN; j++) {
						vertBufData.push_back(locs.at((elems.at(0) - 1) * locN + j));
						//std::cout << "loc" << std::endl;
					}
					if (facN == 0) 
						facN = i;
				}
				if (i >= 2) {
					if (elems.at(1) != 0) {
						for (int j = 0; j < texN; j++) {
							vertBufData.push_back(texs.at((elems.at(1) - 1) * texN + j));
							//std::cout << "tex" << std::endl;
						}
					}
					else {
						//std::cout << "NOOOOOOOOOOOOO" << std::endl;
					}
				}
				if (i >= 3) {
					for (int j = 0; j < norN; j++) {
						//std::cout << "  elemN: " << elems.at(2) << std::endl;
						vertBufData.push_back(nors.at((elems.at(2) - 1) * norN + j));
						//std::cout << "nor" << std::endl;
					}
				}
			}
			facT++;
		}
	}
	/*
	std::cout << "facT: " << facT << std::endl;
	std::cout << "locN: " << locN << std::endl;
	std::cout << "texN: " << texN << std::endl;
	std::cout << "norN: " << norN << std::endl;
	*/
	unsigned int na = locN + texN + norN; // number of attributes

	vertCount = facT * facN;

	// Generate vertex array and buffer (int size (# of arrays), GLuint *arrays)
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// Bind buffers
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	std::cout << na * sizeof(GLfloat) * vertCount << std::endl;
	// Store data in buffer
	glBufferData(GL_ARRAY_BUFFER, na * sizeof(GLfloat) * vertCount, // sizeof(glm::vec3)*vertCount,
		&vertBufData[0], GL_STATIC_DRAW);

	// Describe data to buffer
	glEnableVertexAttribArray(0); // enable a vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, na * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, na * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, na * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));

	// Prepare window and data info
	glClearColor(0.1f, 0.1f, 0.5f, 0.5f); // Sets display-window color to white.
	return true;
}

bool GameObject::buffer() {
	unsigned int na = 5; // number of attributes

	std::vector<GLfloat> locs = {
		// Positions          // Texture Coords
		-1.f, -1.f, 0.0f,  0.0f, 0.0f,  //0
		-1.f, 1.f, 0.0f,   0.0f, 1.0f,  //1
		1.f, 1.f, 0.0f,    1.0f, 1.0f,  //2
		1.f, -1.f, 0.0f,   1.0f, 0.0f,  //3
										// ig
		-1.f, -1.f, 0.0f,  0.0f, 0.0f,  //0
		1.f, 1.f, 0.0f,    1.0f, 1.0f   //2
	};

	// Define location data for a star
	std::vector<unsigned int> locInds = {
		0, 1, 2,
		3, 0, 2
	};

	vertCount = locInds.size();

	// Duplicate data into single buffer for easier processing
	std::vector<GLfloat> vertBufData(vertCount * na);
	/*
	std::cout << sizeof(vertBufData) << std::endl;
	std::cout << vertCount << std::endl;
	std::cout << na << std::endl;
	std::cout << vertCount * na << std::endl;
	*/

	for (unsigned int i = 0; i < vertCount; i++) {
		for (unsigned int j = 0; j < na; j++) {
			vertBufData[i*na + j] = locs[locInds[i] * na + j];
			//std::cout << i*na + j << std::endl;
			//std::cout << vertBufData[i*na + j] << std::endl;
		}
	}
	/*
	for (unsigned int i = 0; i < vertCount * na; i++) {
	if (i % na == 0)
	std::cout << std::endl;
	std::cout << vertBufData[i] << " ";
	}
	std::cout << std::endl << std::endl;

	*/

	// Generate vertex array and buffer (int size (# of arrays), GLuint *arrays)
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// Bind buffers
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// Store data in buffer
	glBufferData(GL_ARRAY_BUFFER, na * sizeof(GLfloat) * vertCount, // sizeof(glm::vec3)*vertCount,
		&vertBufData[0], GL_STATIC_DRAW);

	// Describe data to buffer
	glEnableVertexAttribArray(0); // enable a vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, na * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, na * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	// Prepare window and data info
	glClearColor(0.1f, 0.1f, 0.5f, 0.5f); // Sets display-window color to white.
	return true;
}

bool GameObject::render() {
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount );
	return true;
}