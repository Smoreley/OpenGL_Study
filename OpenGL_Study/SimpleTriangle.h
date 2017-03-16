#pragma once
#include "Progbase.h"

// Demo of simple triangle render
class SimpleTriangle : public Progbase {
private:

	GLuint vao;
	GLuint buffer;

public:
	int start();
	int end();
	int render();
	int update();
};