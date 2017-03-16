#pragma once
#include "Progbase.h"

// 
class TexturedCube : public Progbase {
private:
	GLuint vao;
	GLuint vertex_buffer;
	GLuint color_buffer;
	GLuint coord_buffer;

	GLuint cube_tex;

	GLint proj_loc;
	GLint mov_loc;

public:
	int start();
	int end();
	int render();
	int update();
};