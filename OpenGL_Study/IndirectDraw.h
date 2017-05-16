#pragma once
#include "Progbase.h"

// The draw command struct for indirect draw
struct DrawArraysIndirectCommand
{
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint baseInstance;
};

// Ch7-04
class IndirectDraw : public Progbase
{
public:
	int start();
	int end();
	int render();
	int update(const double);

private:
	double deltaTime;
	double time;

	GLuint m_Vao;

	GLuint m_Indirect_Draw_Buffer;
	GLuint m_Draw_Index_Buffer;

	GLuint vertex_buffer;

	struct {
		GLint mv;
		GLint proj;
		GLint time;
	} m_UniformLocation;

	enum MODE {
		MODE_FIRST,
		MODE_MULTIDRAW,
		MODE_SEPERATE_DRAWS,
		MODE_MAX = MODE_SEPERATE_DRAWS
	} m_Mode;

	GLuint m_Draw_Count = 5000;

};