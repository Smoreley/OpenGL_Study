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

public:
	int start();
	int end();
	int render(double dt);
};