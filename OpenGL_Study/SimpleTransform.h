#pragma once
#include "ProgBase.h"

// Demonstration of translation, rotation, and scaling
class SimpleTransform : public Progbase {
private:
	GLuint rendering_program;

	GLuint vao;

	GLuint vertex_buffer;
	GLuint color_buffer;

	GLuint mv_location;
	GLuint proj_location;

public:
	int start();
	int end();
	int render(double dt);

};