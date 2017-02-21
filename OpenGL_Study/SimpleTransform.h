#pragma once
#include "ProgBase.h"

// Demonstration of translation, rotation, and scaling
class SimpleTransform : public Progbase {
private:
	GLuint rendering_program;

public:
	int start();
	int end();
	int render(double dt);

};