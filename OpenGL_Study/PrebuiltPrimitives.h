#pragma once
#include <GL/glew.h>

namespace Helper {
	// Triangle Vertex Positions
	static const GLfloat triangle_vp[] = {
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	// Pyramid Vertex Positions
	static const GLfloat pyramid_vp[] = {
		-1.0f, -1.0f, 1.0f, // Front
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f, // Left
		-1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, -1.0f, 1.0f, // Right
		1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, -1.0f, -1.0f, // Back
		-1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,

		// Bottom
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,

		1.0, -1.0, 1.0,
		-1.0, -1.0, 1.0,
		1.0, -1.0, -1.0
	};

	// Cube Vertex Positions
	static const GLfloat cube_vp[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	// TODO: Add circle primitive

}