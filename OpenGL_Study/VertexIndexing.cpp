#include "VertexIndexing.h"

int VertexIndexing::start() {
	std::cout << "Vertex Indexing Study" << std::endl;
	rendering_program = Helper::compileShaders("transform.vert", "depthvisualization.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat vertex_positions[] = {
		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,
		0.25f,  0.25f, -0.25f,
		0.25f, -0.25f,  0.25f,
		0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f,  0.25f,
		-0.25f,  0.25f,  0.25f,
	};

	static const GLushort vertex_indices[] = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		6, 0, 2,
		2, 4, 6,
		7, 5, 3,
		7, 3, 1
	};

	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
	
	mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");

	// Enables
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return EXIT_SUCCESS;
}

int VertexIndexing::end() {
	glUseProgram(0);

	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &index_buffer);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int VertexIndexing::render() {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	// Projection
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

	// Movement
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, 0, -1 * (glm::sin((float)glfwGetTime())+1.5f) ));
	mv = glm::rotate(mv, (float)glfwGetTime(), glm::vec3(1.0f, 0.5f, 0.0f));
	glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	return EXIT_SUCCESS;
}

int VertexIndexing::update() {



	return EXIT_SUCCESS;
}