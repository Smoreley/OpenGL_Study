#pragma once
#include "Progbase.h"

class VertexIndexing : public Progbase
{
private:
	GLuint vao;

	GLuint position_buffer;
	GLuint index_buffer;
	GLuint color_buffer;

	GLint mv_loc;
	GLint proj_loc;

public:
	int start();
	int end();
	int render();
	int update();
};