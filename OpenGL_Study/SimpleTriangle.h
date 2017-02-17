#pragma once
#include "progbase.h"

class SimpleTriangle : public Progbase {
private:

	GLuint vao;
	GLuint buffer;

public:
	void start();
	void end();
	void render(double dt);
};