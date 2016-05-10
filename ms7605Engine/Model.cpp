#include "Model.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model() {}

Model::~Model() {}

bool Model::buffer(std::string objfile) {
	std::ifstream file;
	file.open(objfile);
	std::string line;
	int num_elements;
	int locN = 0, texN = 0, norN = 0, facN = 0;
	int locT = 0, texT = 0, norT = 0;
	std::vector<GLfloat> locs;
	std::vector<GLfloat> texs;
	std::vector<GLfloat> nors;
	std::vector<GLfloat> vertBufData;

	bool pLoc = true, pTex = true, pNor = true;

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
			facN++;
		}
	}
	std::cout << "facN: " << facN << std::endl;
	std::cout << "locN: " << locN << std::endl;
	std::cout << "texN: " << texN << std::endl;
	std::cout << "norN: " << norN << std::endl;

	unsigned int na = locN + texN + norN; // number of attributes

	vertCount = facN;

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

bool Model::render() {
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}