#include "SimpleTriangle.h"

int SimpleTriangle::start() {
	std::cout << "Simple Triangle Study" << std::endl;
	rendering_program = Helper::compileShaders("simple.vert", "simplecolor.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat vertex_positions[] = {
		-0.5, 0.5, 0,
		-0.5, -0.5, 0,
		0.5, -0.5, 0
	};

	// Generate buffer
	glGenBuffers(1, &buffer);
	// Specifies the target to which the buffer object is bound
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// used to update the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	return EXIT_SUCCESS;
}

int SimpleTriangle::end() {
	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int SimpleTriangle::render(double dt) {
	// Clear
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clear_color);

	// Activate our program
	glUseProgram(rendering_program);

	// Draw points
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, 3);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	return EXIT_SUCCESS;
}