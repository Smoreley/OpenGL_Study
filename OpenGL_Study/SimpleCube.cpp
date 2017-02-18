#include "SimpleCube.h"

int SimpleCube::start() {
	std::cout << "Simple Cube Study" << std::endl;


	return EXIT_SUCCESS;
}

int SimpleCube::end() {

	return EXIT_SUCCESS;
}

int SimpleCube::render(double dt) {
	static const GLfloat clearColor[] = { 0.25, 0.25, 0.5, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clearColor);

	return EXIT_SUCCESS;
}