#pragma once
#include "Progbase.h"

// Rotating Cube
class SimpleCube : public Progbase {
private:
	GLuint rendering_program;
	GLuint vao;	// Vertex Array Object
	GLuint vbo; // Vertex Buffer Object

	// Buffers
	GLuint vertex_buffer;
	GLuint color_buffer;

	GLint mv_location;
	GLint proj_location;

	//GLuint ibo;	// Index buffer object
	//std::vector<unsigned int> indices;

public:
	int start();
	int end();
	int render(double dt);
};