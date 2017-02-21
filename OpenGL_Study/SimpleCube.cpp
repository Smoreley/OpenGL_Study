#include "SimpleCube.h"

int SimpleCube::start() {
	std::cout << "Simple Cube Study" << std::endl;

	// Program
	rendering_program = Helper::compileShaders("simpletransform.vert", "simpletcolor.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat vertex_positions[] = {
		-0.5, 0.5, 0.5,
		-0.5,-0.5, 0.5,
		0.5,-0.5, 0.5,

		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5
	};

	static const GLfloat vertex_colors[] = {
		1.0, 1.0, 1.0,
		0.0, 0.0, 0.0,
		1.0, 1.0, 1.0,

		0.0, 0.0, 0.0,
		1.0, 1.0, 1.0,
		0.0, 0.0, 0.0
	};

	// Move/Transform matrix
	mv_location = glGetUniformLocation(rendering_program, "mv_matrix");

	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);


	// Reserve/Generate a name for the buffer
	glGenBuffers(1, &vertex_buffer);

	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	// used to allocate memory using a buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	// Tell OpenGL where in the buffer object our data is
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// Enable automatic filling of the attribute
	glEnableVertexAttribArray(0);

	return EXIT_SUCCESS;
}

int SimpleCube::end() {

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int SimpleCube::render(double dt) {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clear_color);

	// Load shaders into the rendering pipeline
	glUseProgram(rendering_program);

	// Translation
	glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f * glm::cos(glfwGetTime()/0.25), 0.5f * glm::sin(glfwGetTime()), 0.0f));
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

	return EXIT_SUCCESS;
}