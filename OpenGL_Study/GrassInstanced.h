#pragma once
#include "Progbase.h"

// Chapter 7 - Instanced
class GrassInstanced : public Progbase {
private:
	double deltaTime;
	double time;

	GLuint vao;	// Vertex Array Object

	GLuint grass_buffer;
	//GLuint index_buffer;

	GLuint grass_length_texture;

	struct {
		GLint mv;
		GLint proj;
		GLint time;
	} uniform_locations;

public:
	int start();
	int end();
	int render();
	int update(double dtime);
};
