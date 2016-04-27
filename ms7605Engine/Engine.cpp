#include "Engine.h"

Engine::Engine() {}

Engine::~Engine() {
	//glDeleteTextures(1, &texID);
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


bool Engine::bufferModel() {
	// Define objects
	auto back = std::make_shared<Object2D>();
	back->set_loc(vec3(-1, 0., 0.2));
	back->set_dim(vec3(2., 1., 1.));
	back->set_texture_dir("Images/sky.jpg");
	back->toggle_wrap();
	om.addObject("back", std::move(back));

	auto floor = std::make_shared<Object2D>();
	floor->set_loc(vec3(-1, -1., 0.2));
	floor->set_dim(vec3(2., 1., 1.));
	floor->set_texture_dir("Images/floor.jpg");
	floor->toggle_wrap();
	om.addObject("floor", std::move(floor));
	
	auto thief = std::make_shared<Player2D>();
	thief->set_loc(vec3(0.0, 0.0, 0));
	thief->set_dim(vec3(0.4, 0.7, 1.0));
	thief->set_texture_dir("Images/thief.png");
	thief->set_behavior(Player2D::CONTROLLED);
	thief->set_label(Player2D::PLAYER);
	thief->set_bound(Player2D::SQUARE);
	thief->set_max_force(0.7f);
	thief->set_max_speed(0.7f);
	thief->set_max_acceleration(0.3f);
	om.addObject("thief", std::move(thief));

	auto mes = std::make_shared<Object2D>();
	mes->set_dim(vec3(0.5, 0.4, 1.0));
	mes->set_texture_dir("Images/ouch.png");
	mes->set_invisibility(true);
	om.addObject("ouch", std::move(mes));

	auto lord1 = std::make_shared<Object2D>();
	lord1->set_loc(vec3(-0.4, -0.4, 0));
	lord1->set_dim(vec3(0.4, .6, 1.));
	lord1->set_texture_dir("Images/lord.png");
	lord1->set_target(om.objects.at("thief"));
	lord1->set_behavior(Object2D::SEEK);
	lord1->set_label(Player2D::ENEMY);
	lord1->set_bound(Player2D::SQUARE);
	lord1->set_max_force(0.3f);
	lord1->set_max_speed(0.2f);
	om.addObject("lord1", std::move(lord1));

	auto lord2 = std::make_shared<Object2D>();
	lord2->set_loc(vec3(-0.7, -0.4, 0));
	lord2->set_dim(vec3(0.6, 0.7, 1.));
	lord2->set_texture_dir("Images/lord2.png");
	lord2->set_target(om.objects.at("thief"));
	lord2->set_behavior(Object2D::SEEK);
	lord2->set_label(Player2D::ENEMY);
	lord2->set_bound(Player2D::SQUARE);
	lord2->set_max_force(0.4f);
	lord2->set_max_speed(0.3f);
	om.addObject("lord2",std::move(lord2));

	return true;
}

bool Engine::gameLoop() {
	clock_t oldtime = std::clock();
	// Game loop; loop until the user closes the window.
	while (!glfwWindowShouldClose(GLFWwindowPtr)) { // <-- true if window was told to close at last frame
													// Update physical simulation, draw buffered models, process input/window events
													// v-- Needed for window events
													//		- Events queue up during a frame
													//			* Dragging screen or pressing key
		clock_t clocks = clock();
		float time_d = (clocks - oldtime)/(float) CLOCKS_PER_SEC;
		oldtime = clocks;

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		om.checkCollisions();

		// Draw objects
		for (iter it = om.objects.begin(); it != om.objects.end(); it++) {
			GameObject *cur = om.objects.at(it->first).get();
			if (!cur->invisible) {
				//texID = i;
				cur->set_target(om.objects.at("thief"));
				cur->set_time_d(time_d);
				cur->update();

				glm::mat4 trans = glm::translate(glm::mat4(1.0f), cur->loc);
				glm::mat4 rot = glm::yawPitchRoll(cur->rot.x, cur->rot.y, cur->rot.z);
				glm::mat4 scale = glm::scale(cur->dim);
				cur->owm = trans * rot * scale;
				glUniformMatrix4fv(1, 1, GL_FALSE, &cur->owm[0][0]);
				glUniform1i(3, cur->flip);
				glBindTexture(GL_TEXTURE_2D, cur->texture);
				//printOnce = false;
				glBindVertexArray(om.vertArr);
				glDrawArrays(GL_TRIANGLES, 0, cur->vert_num); //vertNum.at(i));
			}
		}

		// Key input
		if (InputManager::press(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);

		// Swaps fron (what sceen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(GLFWwindowPtr);
	}
	glfwTerminate(); // <- Must be called before engine closes, else memory leaks.
	return true;
}

bool Engine::useShaders() {
	// Input loader
	InputManager::init(GLFWwindowPtr);

	// Texture Loading
	// Add a map later to avoid loading the same texture multiple times.
	for (iter it = om.objects.begin(); it != om.objects.end(); it++) {
		std::string i = it->first;
		GameObject* current = om.objects.at(it->first).get();
		current->set_texture(useTexture(current->texDir, current->wrap));
		//useTexture(om.objects.at(i)->texDir, om.objects.at(i)->wrap);
	}

	// Shader Loading
	GLuint index = shader_manager.loadShaders("Shaders/vShader.glsl",
		"Shaders/fShader.glsl");
	if (index == true) {
		glUseProgram(shader_manager.getProgram());
		return true;
	}
	return false;
}

GLuint Engine::useTexture(char* texDir, bool wrap) {
	FIBITMAP* imagePtr =
		FreeImage_ConvertTo32Bits(
			FreeImage_Load(
				FreeImage_GetFileType(texDir, 0), texDir)
			);
	GLuint texture;
	glGenTextures(1, &texture); // i used to be 1
	glBindTexture(GL_TEXTURE_2D, texture);

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
	return texture;
}