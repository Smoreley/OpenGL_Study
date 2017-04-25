#include "GrassInstanced.h"
#include "Helper.h"

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
	uniform_locations.mv = glGetUniformLocation(rendering_program, "mv_matrix");
	uniform_locations.proj = glGetUniformLocation(rendering_program, "proj_matrix");
	uniform_locations.time = glGetUniformLocation(rendering_program, "u_time");


	glActiveTexture(GL_TEXTURE0);
	grass_length_texture = Helper::createTexture("assets/grass_length.dds");

	// Enables
	/*glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);*/
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	time = 0;
	return EXIT_SUCCESS;
}

int GrassInstanced::end() {
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteTextures(1, &grass_length_texture);

	glDeleteBuffers(1, &grass_buffer);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int GrassInstanced::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100000.0f);
	glUniformMatrix4fv(uniform_locations.proj, 1, GL_FALSE, glm::value_ptr(proj));

	// Model View Matrix
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, 0, 0));

	float r = 80.0f;

	mv = glm::lookAt(
		glm::vec3(sinf(time) * r, 25.0f, cosf(time) * r),
		glm::vec3(0.0f, -20.0f, 0.0f),
		glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(uniform_locations.mv, 1, GL_FALSE, glm::value_ptr(mv));

	// Send time
	glUniform1f(uniform_locations.time, time);

	//glViewport(0, 0, 1280, 720);
	//glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, glm::pow(256, 2) );

	return EXIT_SUCCESS;
}

#include <thread>
#include <chrono>

int GrassInstanced::update(double dtime) {
	deltaTime = dtime;
	time += deltaTime/10.0f;

	float outcome = 0;
	outcome = float(32 >> 4);
	//std::cout << "Testing numbers: " << sizeof(int) << std::endl;

	return EXIT_SUCCESS;
}

