#pragma once
#include "stdafx.h"
#include "Helper.h"

class Progbase {
private:

protected:
	GLuint rendering_program;

public:
	virtual int start() = 0;
	virtual int end() = 0;
	virtual int render() = 0;
	virtual int update(double dtime) = 0;

};