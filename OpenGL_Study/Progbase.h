#pragma once

#include "Helper.h"

#include <iostream>>

#include <Gl/glew.h>
#include <glm\glm.hpp>

class Progbase {
private:


protected:
	// 
	GLuint rendering_program;

public:

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void render(double dt) = 0;
};