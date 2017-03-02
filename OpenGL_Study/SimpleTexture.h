#pragma once
#include "Progbase.h"

// Demo of applying a texture
class SimpleTexture : public Progbase {
private:
	GLuint vao;

	GLuint vertex_buffer;

	GLint mv_location;
	GLint proj_location;
	
	GLuint texture;

public:
	int start();
	int end();
	int render(double dt);

};