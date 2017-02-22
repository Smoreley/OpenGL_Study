#include "SimpleCube.h"

int SimpleCube::start() {
	std::cout << "Simple Cube Study" << std::endl;

	// Program
	rendering_program = Helper::compileShaders("simpletransform.vert", "simplecolor.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Cube vertex Positions
	static const GLfloat vertex_positions[] = {
		// Front
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,

		0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,

		// Top
		-0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,
		0.5, 0.5, -0.5,

		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,
		
		// Back
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,

		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,

		// Bottom
		-0.5, -0.5, 0.5,
		0.5, -0.5, -0.5,
		-0.5, -0.5, -0.5,

		0.5, -0.5, 0.5,
		0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5,

		// Left
		-0.5, -0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,

		-0.5, -0.5, 0.5,
		-0.5, -0.5, -0.5,
		-0.5, 0.5, 0.5,

		// Right
		0.5, -0.5, -0.5,
		0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,

		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, -0.5

	};

	// Vertex Colors
	static const GLfloat vertex_colors[] = {
		// Front
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		// Top
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		// Back
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,

		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,

		// Bottom
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,

		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,

		// Left
		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,

		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,

		// Right
		1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0,

		1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0
	};

	// Move/Transform matrix
	mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_location = glGetUniformLocation(rendering_program, "proj_matrix");

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

	// Bind the color buffer and initialize it
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// Enable
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return EXIT_SUCCESS;
}

int SimpleCube::end() {

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int SimpleCube::render(double dt) {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// Load shaders into the rendering pipeline
	glUseProgram(rendering_program);

	// Projection into screen space
	static const float aspect = 1280.0f / 720.0f;
	glm::mat4 proj = glm::perspective(1.0472f, aspect, 0.1f, 100.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

	// Translation set through uniform
	glm::mat4 mv_matrix = glm::mat4(1.0f);
	// Translate cube
	mv_matrix = glm::translate(mv_matrix, glm::vec3(
		0.0f,
		0.0f,
		-6.0f + 5 * glm::sin(glfwGetTime())
	));

	// Rotate along an axis
	mv_matrix = glm::rotate(mv_matrix, (float)glfwGetTime(), glm::vec3(2.0f, 1.0f, 0.0f));
	// Set move uniform
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 36);

	return EXIT_SUCCESS;
}