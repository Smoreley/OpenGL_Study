#pragma once
#include "Progbase.h"

// Rendering multiple cubes at once
class MultiCubeRendering : public Progbase
{
private:
	double deltaTime;
	double time;

	GLuint vao;
	GLuint vertex_buffer;
	GLuint color_buffer;

	GLint proj_loc;
	GLint mov_loc;

	static const int cube_number = 16;
	glm::vec3 cube_trans[cube_number];
	glm::vec3 cube_rotation[cube_number];
	glm::vec3 cube_scale[cube_number];
	
public:
	int start();
	int end();
	int render();
	int update(double);

};