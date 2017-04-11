#include "QuadInstanced.h"

int QuadInstanced::start() {
	std::cout << "Quad Instancing Study" << std::endl;

	rendering_program = Helper::compileShaders("instanced.vert", "simplecolor.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat vertex_pos[] =
	{
		-0.5f, -0.5f, -0.0f, 1.0f,
		0.5f, -0.5f, -0.0f, 1.0f,
		0.5f,  0.5f, -0.0f, 1.0f,
		-0.5f,  0.5f, -0.0f, 1.0f,
	};

	static const GLfloat vertex_color[] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};

	static const GLfloat instance_offset[] =
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	};

	GLuint offset = 0;

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_pos) + sizeof(vertex_color) + sizeof(instance_offset), NULL, GL_STATIC_DRAW);

	// Load the data into the array buffer
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex_pos), vertex_pos);
	offset += sizeof(vertex_pos);

	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex_color), vertex_color);
	offset += sizeof(vertex_color);

	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_offset), instance_offset);
	offset += sizeof(instance_offset);

	// Set location of attributes tied to the data we just loaded into the buffer
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertex_pos));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(vertex_pos) + sizeof(vertex_color)));

	// Enable attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Here we are saying first which attribute we are referring to.
	// Second, the number of instances before the attribute is updated (0 will be per-vertex instead of per-instance)
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);


	return EXIT_SUCCESS;
}

int QuadInstanced::end() {
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int QuadInstanced::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);

	glUseProgram(rendering_program);

	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 5);

	return EXIT_SUCCESS;
}

int QuadInstanced::update() {
	
	return EXIT_SUCCESS;
}