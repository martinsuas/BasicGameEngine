#include "Engine.h"
#include <iostream>


int main(int argc, char** argv) {
	Engine e;
	if (!e.init()) return -1;
	if (!e.bufferModel()) return -1;
	if (e.useShaders() == 0) return -1;
	e.gameLoop();
	return 0;
}