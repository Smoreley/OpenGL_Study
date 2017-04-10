#pragma once
#include "Progbase.h"

// Ch7-04
class IndirectDraw : public Progbase
{
public:

	int start();
	int end();
	int render();
	int update();

private:

	GLuint m_Vao;

	GLuint m_Indirect_Draw_Buffers;
	GLuint m_Draw_Index_Buffer;

	struct {
		GLint mv;
		GLint proj;
		GLint time;
	} m_UniformLocation;

	enum MODE {
		MODE_FIRST,
		MODE_MULTIDRAW,
		MODE_SEPERATE_DRAW,
		MODE_MAX = MODE_SEPERATE_DRAW
	} m_Mode;

	GLuint m_Draw_Count = 500;

};