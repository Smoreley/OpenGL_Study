#include "MultiCubeRendering.h"
#include "Helper.h"

int MultiCubeRendering::start() {
	std::cout << "Multiple Cube Rendering" << std::endl;
	rendering_program = Helper::compileShaders("transform.vert", "simplecolor.frag");

	// Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// (VBO) Vertex position attributes
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// Colors
	static  GLfloat vertex_colors[200];
	std::fill_n(vertex_colors, 200, 0.0f);

	for (int i = 0; i < 200; i += 4) {
		*(vertex_colors + i + 1) = sin((i % 9) / 9.0f);
		*(vertex_colors + i + 2) = cos((i % 9) / 9.0f);
	}

	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// Get uniform location in program
	mov_loc = glGetUniformLocation(rendering_program, "u_mv_matrix");
	proj_loc = glGetUniformLocation(rendering_program, "u_proj_matrix");

	// Enables
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Depth test for multiple objects so further object are occluded
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Fill in position, rotation, and scale arrays for cubes
	std::fill_n(cube_trans, cube_number, glm::vec3(0.0f, 0.0f, -30.0f));
	std::fill_n(cube_rotation, cube_number, glm::vec3(0.0f));
	std::fill_n(cube_scale, cube_number, glm::vec3(1.0f));

	time = 0;
	return EXIT_SUCCESS;
}

int MultiCubeRendering::end() {
	glUseProgram(0);

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int MultiCubeRendering::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	glm::mat4 proj_matrix = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj_matrix));

	for (int i = 0; i < cube_number; i++) {

		glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), cube_trans[i]);

		// Rotation
		mv_matrix = glm::rotate(mv_matrix, cube_rotation[i].x, glm::vec3(1.0, 0.0f, 0.0f));
		mv_matrix = glm::rotate(mv_matrix, cube_rotation[i].y, glm::vec3(0.0, 1.0f, 0.0f));
		mv_matrix = glm::rotate(mv_matrix, cube_rotation[i].z, glm::vec3(0.0, 0.0f, 1.0f));	

		mv_matrix = glm::scale(mv_matrix, cube_scale[i]);

		glUniformMatrix4fv(mov_loc, 1, GL_FALSE, glm::value_ptr(mv_matrix));

		glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
	}

	return EXIT_SUCCESS;
}

int MultiCubeRendering::update(double dtime) {
	deltaTime = dtime;
	time += deltaTime;


	for (int i = 0; i < cube_number; i++) {
		float f = (float)i + (float)time * 0.1f * i;
		cube_trans[i] = glm::vec3(
			sinf(2.3f * f) * 2.0f,
			cosf(2.3 * f) *(i/10.0f),
			(sinf(2.3f * f) - 23 + (1.2f * i))
		);

		cube_rotation[i] = glm::vec3(
			sinf(time / 2.0f) + i * 2,
			time + i,
			0.0f
		);

		cube_scale[i] = glm::vec3((sin(time * 10.0f) + 5.0f) / 8.0f);
	}

	return EXIT_SUCCESS;
}