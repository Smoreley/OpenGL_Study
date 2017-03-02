#include "FlyingCamera.h"

int FlyingCamera::start() {
	std::cout << "Flying Camera Demo" << std::endl;

	// Program
	rendering_program = Helper::compileShaders("camera.vert", "simplecolor.freg");

	glGenVertexArrays(1, &vao);

	GLint temp = glGetUniformBlockIndex(rendering_program, "TransformBlock");


	return EXIT_SUCCESS;
}

int FlyingCamera::end() {

	glUseProgram(0);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int FlyingCamera::render(double dt) {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clear_color);

	// TODO: Implement Rendering code


	return EXIT_SUCCESS;
}