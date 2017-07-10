#pragma once

// Chapter 
class VertexIndexing : public Progbase
{
private:
	double deltaTime;
	double time;

	GLuint vao;

	GLuint position_buffer;
	GLuint index_buffer;
	GLuint color_buffer;

	GLint mv_loc;
	GLint proj_loc;

public:
	int start();
	int end();
	int render();
	int update(double);
};