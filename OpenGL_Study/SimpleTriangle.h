#pragma once
#include "Progbase.h"

class SimpleTriangle : public Progbase {
private:

	GLuint vao;
	GLuint buffer;

public:
	int start();
	int end();
	int render(double dt);
};