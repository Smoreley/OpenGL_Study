#pragma once
#include "Progbase.h"

// Ch7-02
class GrassInstanced : public Progbase {
private:

	// Vertex Array Object
	GLuint vao;

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
	int update();

};
