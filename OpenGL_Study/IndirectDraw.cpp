#include "IndirectDraw.h"
#include "Helper.h"

int IndirectDraw::start() {
	std::cout << "Indirect Multi Drawing Study" << std::endl;

	// Lets set up array for multi draw
	GLfloat *myArray;
	int calculated_size = (sizeof(Helper::cube_vp) + sizeof(Helper::pyramid_vp))/sizeof(GLfloat);
	myArray = new GLfloat[calculated_size];

	for (int i = 0; i < (sizeof(Helper::cube_vp)/sizeof(GLfloat)); i++) {
		myArray[i] = Helper::cube_vp[i];
	}

	for (int j = 0; j < (sizeof(Helper::pyramid_vp) / sizeof(GLfloat)); j++) {
		myArray[j + (sizeof(Helper::cube_vp) / sizeof(GLfloat))] = Helper::pyramid_vp[j];
	}

	rendering_program = Helper::compileShaders("indirect.vert", "simplecolor.frag");

	// Generate a name for a new array
	glGenVertexArrays(1, &m_Vao);
	// Makes the vertex array object active
	glBindVertexArray(m_Vao);

	// Vertex Buffer
	/*glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myArray), myArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);*/
	//delete[] myArray;

	// Reserve/Generate a name for the buffer
	glGenBuffers(1, &vertex_buffer);
	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	// used to allocate memory using a buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	// Tell OpenGL where in the buffer object our data is
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// Enable automatic filling of the attribute
	glEnableVertexAttribArray(0);


	// Indirect Draw Buffers
	glGenBuffers(1, &m_Indirect_Draw_Buffer);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_Indirect_Draw_Buffer);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, m_Draw_Count * sizeof(DrawArraysIndirectCommand), NULL, GL_STATIC_DRAW);

	DrawArraysIndirectCommand *cmd = (DrawArraysIndirectCommand*) glMapBufferRange(
		GL_DRAW_INDIRECT_BUFFER,
		0,
		m_Draw_Count * sizeof(DrawArraysIndirectCommand),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
	);

	for (int i = 0; i < m_Draw_Count; i++) {
		cmd[i].first = 0;
		cmd[i].count = (sizeof(Helper::cube_vp)/sizeof(GLfloat));
		//cmd[i].count = sizeof(Helper::cube_vp);

		cmd[i].primCount = 1;
		cmd[i].baseInstance = i;
	}
	glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);


	// Draw Index Buffer
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
	glUnmapBuffer(GL_ARRAY_BUFFER);


	// Attrib
	glVertexAttribIPointer(10, 1, GL_UNSIGNED_INT, 0, NULL);
	glVertexAttribDivisor(10, 1);
	glEnableVertexAttribArray(10);

	// Get Uniform Locations
	m_UniformLocation.mv = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_UniformLocation.proj = glGetUniformLocation(rendering_program, "u_proj_matrix");
	m_UniformLocation.time = glGetUniformLocation(rendering_program, "u_time");

	// Enable
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	time = 0;

	return EXIT_SUCCESS;
}

int IndirectDraw::end() {
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_Indirect_Draw_Buffer);
	glDeleteBuffers(1, &m_Draw_Index_Buffer);
	
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int IndirectDraw::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	// Projection
	glm::mat4 proj = glm::perspective(1.0472f, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 10000.0f);
	
	// Model View
	glm::mat4 mv = glm::mat4(1.0);

	float r = 180.0f;
	mv = glm::lookAt(
		glm::vec3(r, 150.0f * sin(time / 5.0f), r),
		glm::vec3(0.0f, -20.0f * cos(time), 0.0f),
		glm::vec3(0.0, 1.0, 0.0));

	
	// Set Uniform
	glUniformMatrix4fv(m_UniformLocation.proj, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(m_UniformLocation.mv, 1, GL_FALSE, glm::value_ptr(mv));
	glUniform1f(m_UniformLocation.time, time);

	m_Mode = MODE_MULTIDRAW;
	// Draw
	if (m_Mode == MODE_MULTIDRAW) {
		glMultiDrawArraysIndirect(GL_TRIANGLES, NULL, m_Draw_Count, 0);
		std::cerr << ".";
	}
	else if (m_Mode == MODE_SEPERATE_DRAWS) {
		for (int j = 0; j < m_Draw_Count; j++) {
			GLuint first = 0, count = 1;
			// not done
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, first, count, 1, j);
		}
	}

	return EXIT_SUCCESS;
}

int IndirectDraw::update(const double dtime) {
	deltaTime = dtime;
	time += deltaTime;

	return EXIT_SUCCESS;
}