#include "SimpleTransform.h"

int SimpleTransform::start() {
	std::cout << "Simple Transform Study" << std::endl;
	rendering_program = Helper::compileShaders("simpletransform.vert", "simplecolor.frag");


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

	return EXIT_SUCCESS;
}