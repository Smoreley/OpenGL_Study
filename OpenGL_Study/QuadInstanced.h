#pragma once
#include "Progbase.h"

class QuadInstanced : public Progbase
{
private:

	// Vertex Array Object
	GLuint vao;

	GLuint vbo;

	// Buffers
	GLuint vertex_buffer;
	GLuint color_buffer;
	
	// Uniforms
	struct {
		GLint modelview;
		GLint projection;
	} uniform_loc;

public:
	int start();
	int end();
	int render();
	int update();

};