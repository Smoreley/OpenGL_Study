#pragma once
#include "Progbase.h"

class GrassInstanced : public Progbase {
private:

	// Vertex Array Object
	GLuint vao;

	GLuint grass_buffer;
	GLuint index_buffer;

	//struct {
	//	GLint mv;
	//	GLint proj;
	//} uniform_locations;

	GLint mv_loc;
	GLint proj_loc;

public:
	int start();
	int end();
	int render();
	int update();

};
