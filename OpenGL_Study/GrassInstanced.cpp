#include "GrassInstanced.h"

int GrassInstanced::start() {
	std::cout << "Grass Instancing Study" << std::endl;

	// Program
	rendering_program = Helper::compileShaders("grass.vert", "simplecolor.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat grass_blade[] = {
		-0.3f, 0.0f,
		0.3f, 0.0f,
		-0.20f, 1.0f,
		0.1f, 1.3f,
		-0.05f, 2.3f,
		0.0f, 3.3f
	};

	glGenBuffers(1, &grass_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, grass_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grass_blade), grass_blade, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	// Get uniform locations
	mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");

	// Enables
	/*glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);*/
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return EXIT_SUCCESS;
}

int GrassInstanced::end() {
	glUseProgram(0);


	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int GrassInstanced::render() {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100000.0f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

	// Model View Matrix
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, 0, -5));

	float time = (float)glfwGetTime() / 4.0f;
	float r = 50.0f;

	mv = glm::lookAt(
		glm::vec3(sinf(time) * r, 5.0f, cosf(time) * r),
		glm::vec3(0.0f, -10.0f, 0.0f),
		glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv));

	//glViewport(0, 0, 1280, 720);
	//glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, 32 * 32);

	return EXIT_SUCCESS;
}

int GrassInstanced::update() {

	return EXIT_SUCCESS;
}

