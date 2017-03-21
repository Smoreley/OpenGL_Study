#include "SimpleTransform.h"

int SimpleTransform::start() {
	std::cout << "Simple Transform Study" << std::endl;
	rendering_program = Helper::compileShaders("transform.vert", "simplecolor.frag");

	// Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex Colors
	static const GLfloat vertex_colors[] = {
		// Front
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		
		// Bottom
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,

		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0
	};

	// (VBO) Vertex position attributes 
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::pyramid_vp), Helper::pyramid_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// (VBO) Vertex color attributes
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// Get uniform location in program
	mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_location = glGetUniformLocation(rendering_program, "proj_matrix");

	// Enables
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Depth test for multiple objects so further object are occluded
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return EXIT_SUCCESS;
}

int SimpleTransform::end() {
	// De-select shader program
	glUseProgram(0);

	// Done with buffers delete
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int SimpleTransform::render() {
	// Clear
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 18);

	return EXIT_SUCCESS;
}

int SimpleTransform::update() {

	// Perspective
	glm::mat4 proj = glm::perspective(50.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

	// Movement
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, 0, -20));
	mv = glm::rotate(mv, (float)glfwGetTime(), glm::vec3(glm::cos(glfwGetTime()) * 2.0f, 0.5f, 1.5f));
	mv = glm::scale(mv, glm::vec3(1.0f, 2.0f + glm::sin(glfwGetTime()*2.1f), 1.0f));

	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv));

	return EXIT_SUCCESS;
}