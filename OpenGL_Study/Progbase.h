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

	virtual int start() = 0;
	virtual int end() = 0;
	virtual int render(double dt) = 0;
};