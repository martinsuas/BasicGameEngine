#include "Engine.h"
#include <iostream>
#include <memory>

Engine::Engine() {}

Engine::~Engine() {
	//delete GLFWwindowPtr;
	glDeleteTextures(1, &texID);
}

bool Engine::init() {
	// Initializes GLFW
	if (glfwInit() == GL_FALSE)
		return false;
	GLFWwindowPtr = glfwCreateWindow(1280, 900, "ms7605 DSA1 Engine",
		NULL, NULL);

	// Make our pointer the currently active window, else quit
	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return false;
	}
	// Initializes GLEW or quit
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}
	return true;
}

bool Engine::addObject(std::shared_ptr<Character2D> obj) {
	objects.push_back(obj);
	//float lx, ux, ly, uy;
	//lx = obj.trans.loc.x - obj.trans.size.x / 2;
	//ux = obj.trans.loc.x - obj.trans.size.x / 2;
	//ly = obj.trans.loc.x - obj.trans.size.x / 2;
	//uy = obj.trans.loc.x - obj.trans.size.x / 2;

	std::vector<glm::vec3> locs = {
		{ 0., 1., 0.0 }, //0
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
	vertNum.push_back(vertCount);
	// Duplicate data into single buffer for easier processing
	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
		vertBufData[i] = locs[locInds[i]];

	// Generate vertex array and buffer
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
	glClearColor(0.1, 0.1, 0.5, 0.5); // Sets display-window color to white.
	return true;
}
bool Engine::bufferModel() {
	// Define objects
	//std::unique_ptr<Character2D> sky(new Character2D("Images/sky.jpg"),
		//vec3(0,0,0), vec3(), vec3(1.,1.,1.));
	//sky->toggle_wrap();
	//addObject(sky);

	//Character2D *floor = new Character2D("Images/floor.jpg", 
		//vec3(0,-1.,0), vec3(), vec3(1., 1., 1.));
	//floor->toggle_wrap();

	auto floor = std::make_unique<Character2D>();
	floor->set_loc(vec3(0, -1., 0));
	floor->set_dim(vec3(1., 1., 1.));
	floor->set_texture("Images/floor.jpg");
	floor->toggle_wrap();
	addObject(std::move(floor));
	
	//Player *thief = new Player("Images/thief.png", vec3(0.2, -0.4, 0), vec3(), vec3(1, 1, 1));
	auto thief = std::make_unique<Player>();
	thief->set_loc(vec3(0.2, -0.4, 0));
	thief->set_dim(vec3(1., 1., 1.));
	thief->set_texture("Images/thief.png");
	thief->set_behavior(Player::PLAYER);
	thief->set_max_force(0.15f);
	thief->set_max_speed(0.1f);
	thief->set_max_acceleration(0.1f);
	addObject(std::move(thief));
	/*
	Character2D *lord1 = new Character2D("Images/lord.png",
		vec3(-0.4, -0.4, 0), vec3(), vec3(1, 1, 1));
	lord1->set_target(thief->loc);
	lord1->set_behavior(Character2D::SEEK);
	lord1->set_max_force(0.015);
	lord1->set_max_speed(0.01);
	addObject(lord1);

	Character2D *lord2 = new Character2D("Images/lord2.png",
		vec3(-0.7, -0.4, 0), vec3(), vec3(1, 1, 1));
	lord2->set_target(thief->loc);
	lord2->set_behavior(Character2D::SEEK);
	lord2->set_max_force(0.02);
	lord2->set_max_speed(0.015);
	addObject(lord2);
	*/

	return true;
}

bool Engine::gameLoop() {
	printOnce = true;
	// Game loop; loop until the user closes the window.
	while (!glfwWindowShouldClose(GLFWwindowPtr)) { // <-- true if window was told to close at last frame
													// Update physical simulation, draw buffered models, process input/window events
													// v-- Needed for window events
													//		- Events queue up during a frame
													//			* Dragging screen or pressing key
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw objects
		//thief.update();
		for (int i = 0; i < objects.size(); i++) {
			//texID = i;
			objects.at(i)->update();
			Character2D *cur = objects.at(i).get();
			glm::mat4 trans = glm::translate(glm::mat4(1.0f), cur->loc);
			glm::mat4 rot = glm::yawPitchRoll(cur->rot.x, cur->rot.y, cur->rot.z);
			glm::mat4 scale =  glm::scale(cur->dim);
			cur->owm = trans * rot * scale;
			glUniformMatrix4fv(1, 1, GL_FALSE, &cur->owm[0][0]);
			useTexture(cur->texDir, cur->wrap);
			glBindTexture(GL_TEXTURE_2D, texID);
			//printOnce = false;
			glBindVertexArray(vertArr);
			//glBindTexture(GL_TEXTURE_2D, texID);
			glDrawArrays(GL_TRIANGLES, 0, vertNum.at(i));
			// Swaps fron (what sceen displays) and back (what OpenGL draws to) buffers.
			//glfwSwapBuffers(GLFWwindowPtr);
		}

		// Key input
		// Esc
		if (InputManager::press(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);

		/*
		// Mouse Click
		if (InputManager::press(GLFW_MOUSE_BUTTON_1)) {
			if (!secondTexture) {
				useTexture("Images/fire.jpg");
				secondTexture = true;
			}
		}
		else {
			if (secondTexture) {
				useTexture("Images/starfish.jpg");
				secondTexture = false;
			}
		}
		*/
		//glBindVertexArray(vertArr);
		//glBindTexture(GL_TEXTURE_2D, texID);
		//glDrawArrays(GL_TRIANGLES, 0, 24);
		// Swaps fron (what sceen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(GLFWwindowPtr);
	}
	glfwTerminate(); // <- Must be called before engine closes, else memory leaks.
	//for (Character2D *o : objects)
		//delete o;
	return true;
}

bool Engine::useShaders() {
	// Input loader
	InputManager::init(GLFWwindowPtr);

	// Texture Loading
	//for (int i = 0; i < objects.size(); i++) {
		//useTexture(objects.at(i).texDir, objects.at(i).wrap, i);
	//}
	//useTexture("Images/starfish.jpg");

	// Shader Loading
	GLuint index = shader_manager.loadShaders("Shaders/vShader.glsl",
		"Shaders/fShader.glsl");
	if (index == true) {
		glUseProgram(shader_manager.getProgram());
		return true;
	}
	return false;
}

void Engine::useTexture(char* texDir, bool wrap) {
	FIBITMAP* imagePtr =
		FreeImage_ConvertTo32Bits(
			FreeImage_Load(
				FreeImage_GetFileType(texDir, 0), texDir)
			);

	glGenTextures(1, &texID); // i used to be 1
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(imagePtr),
		FreeImage_GetHeight(imagePtr),
		0, GL_BGRA, GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(imagePtr));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);

	// Clear from RAM
	FreeImage_Unload(imagePtr);
	// Unbind when finished uplloading
	glBindTexture(GL_TEXTURE_2D, 0);
}