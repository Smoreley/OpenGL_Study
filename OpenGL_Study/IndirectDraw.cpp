#include "IndirectDraw.h"

int IndirectDraw::start() {
	std::cout << "Indirect Drawing Study" << std::endl;

	rendering_program = Helper::compileShaders("indirect.vert", "simplecolor.frag");

	// Generate a name for a new array
	glGenVertexArrays(1, &m_Vao);
	// Makes the vertex array object active
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Indirect_Draw_Buffers);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_Indirect_Draw_Buffers);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, m_Draw_Count * sizeof(Helper::cube_vp), NULL, GL_STATIC_DRAW);
	glMapBufferRange(
		GL_DRAW_INDIRECT_BUFFER,
		0,
		m_Draw_Count * sizeof(Helper::cube_vp),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
	);

	for (int i = 0; i < m_Draw_Count; i++) {
		
	}


	glGenBuffers(1, &m_Draw_Index_Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Draw_Index_Buffer);
	glBufferData(GL_ARRAY_BUFFER, m_Draw_Count * sizeof(GLuint), NULL, GL_STATIC_DRAW);

	GLuint *pDraw_Index = (GLuint *)glMapBufferRange(
		GL_ARRAY_BUFFER, 
		0,
		m_Draw_Count * sizeof(GLuint), 
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
	);

	for (int i = 0; i < m_Draw_Count; i++) {
		pDraw_Index[i] = i;
	}



	// Get Uniform Locations
	m_UniformLocation.mv = glGetUniformLocation(rendering_program, "mv_matrix");
	m_UniformLocation.proj = glGetUniformLocation(rendering_program, "proj_matrix");
	m_UniformLocation.time = glGetUniformLocation(rendering_program, "u_time");


	return EXIT_SUCCESS;
}

int IndirectDraw::end() {
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_Indirect_Draw_Buffers);
	glDeleteBuffers(1, &m_Draw_Index_Buffer);
	
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int IndirectDraw::render() {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };

	glClearBufferfv(GL_COLOR, 0, clear_color);

	
	glUseProgram(rendering_program);

	return EXIT_SUCCESS;
}

int IndirectDraw::update() {

	return EXIT_SUCCESS;
}