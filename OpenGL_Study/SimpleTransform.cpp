#include "SimpleTransform.h"

int SimpleTransform::start() {
	std::cout << "Simple Transform Study" << std::endl;
	rendering_program = Helper::compileShaders("simpletransform.vert", "simplecolor.frag");

	// Pyramid vertex positions
	static const GLfloat vertex_positions[] = {
		// Bottom
		-1,-1, -1,
		-1,-1, 1,
		1,-1, 1
	};


	return EXIT_SUCCESS;
}

int SimpleTransform::end() {

	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int SimpleTransform::render(double dt) {
	// Clear
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clear_color);

	// Draw
	// TODO: Implement drawing ode

	return EXIT_SUCCESS;
}