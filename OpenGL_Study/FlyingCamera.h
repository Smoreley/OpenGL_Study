#pragma once
#include "Progbase.h"

class FlyingCamera : public  Progbase {
private:

	GLuint vao;

	// Uniforms
	GLuint mv_location;
	GLuint proj_location;

	// Camera
	glm::vec3 camera_pos;
	glm::vec3 camera_forward;


public:
	int start();
	int end();
	int render(double dt);
};