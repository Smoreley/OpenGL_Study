#pragma once
#include "stdafx.h"

struct button_map {
	bool left;
	bool right;
	bool up;
	bool down;
	bool rot_left;
	bool rot_right;
};

class Progbase {
private:

protected:
	GLuint rendering_program;
	button_map bmap;

public:
	virtual int start() = 0;
	virtual int end() = 0;
	virtual int render() = 0;
	virtual int update(const double dtime) = 0;
	void setButtons(button_map bmap) { this->bmap = bmap; }

};