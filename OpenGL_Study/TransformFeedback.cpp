#include "Progbase.h"
#include "TransformFeedback.h"
#include "Helper.h"

/* Forward-declaration */
void load_shader(GLuint& m_updateProgram);

enum BUFFER_TYPE
{
	POS_A,
	POS_B,
	VEL_A,
	VEL_B,
	CONNECTION
};

int TransformFeedback::start() {
	std::cout << "TransformFeedback demo" << std::endl;

	rendering_program = Helper::compileShaders("feedback_render.vert", "feedback.frag");

	//update_program = Helper::compileShaders("feedback_update.vert", "feedback.frag");
	load_shader(update_program);

	// Uniforms
	//m_modelViewLocation = glGetUniformLocation(rendering_program, "u_mv_matrix");
	//m_projectionLocation = glGetUniformLocation(rendering_program, "u_proj_matrix");
	//m_viewLocation = glGetUniformLocation(rendering_program, "u_view_matrix");


	// Initial Positions and velocities of each node
	m_clothPointsTotal = m_clothPointsX * m_clothPointsY;
	vec4* initialPositions = new vec4[m_clothPointsTotal];
	vec3* initialVelocities = new vec3[m_clothPointsTotal];
	ivec4* connectionVectors = new ivec4[m_clothPointsTotal];

	int n = 0;
	for (int j = 0; j < m_clothPointsY; j++) {
		float fj = (float)j / (float)m_clothPointsX;
		for (int i = 0; i < m_clothPointsX; i++) {
			float fi = (float)i / (float)m_clothPointsX;

			initialPositions[n] = vec4((fi - 0.5f) * (float)m_clothPointsX,
				(fj - 0.5f) * (float)m_clothPointsY, 0.6f * sinf(fi) * cosf(fj),
				1.0f);

			initialVelocities[n] = vec3(0.0f);
			connectionVectors[n] = ivec4(-1);

			if (j != (m_clothPointsY - 1)) {
				if (i != 0)
					connectionVectors[n][0] = n - 1;

				if (j != 0)
					connectionVectors[n][1] = n - m_clothPointsX;

				if (i != (m_clothPointsX - 1))
					connectionVectors[n][2] = n + 1;

				if (j != (m_clothPointsY - 1))
					connectionVectors[n][3] = n + m_clothPointsX;
			}
			n++;
		}
	}


	// Vertex Arrays
	glGenVertexArrays(2, m_vao);
	glGenBuffers(5, m_vbo);

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(m_vao[i]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POS_A + i]);
		glBufferData(GL_ARRAY_BUFFER, m_clothPointsTotal * sizeof(vec4), initialPositions, GL_DYNAMIC_COPY);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[VEL_A + i]);
		glBufferData(GL_ARRAY_BUFFER, m_clothPointsTotal * sizeof(vec3), initialVelocities, GL_DYNAMIC_COPY);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[CONNECTION]);
		glBufferData(GL_ARRAY_BUFFER, m_clothPointsTotal * sizeof(ivec4), connectionVectors, GL_STATIC_DRAW);
		glVertexAttribIPointer(2, 4, GL_INT, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	// Cleanup
	delete[] connectionVectors;
	delete[] initialVelocities;
	delete[] initialPositions;

	/* Generate Textures */
	glGenTextures(2, m_tbo);
	glBindTexture(GL_TEXTURE_BUFFER, m_tbo[0]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, m_vbo[POS_A]);
	glBindTexture(GL_TEXTURE_BUFFER, m_tbo[1]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, m_vbo[POS_B]);

	int lines = (m_clothPointsX - 1) * m_clothPointsY + (m_clothPointsY - 1) * m_clothPointsX;

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lines * 2 * sizeof(int), NULL, GL_STATIC_DRAW);

	int * e = (int *)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, lines * 2 * sizeof(int), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int j = 0; j < m_clothPointsY; j++) {
		for (int i = 0; i < m_clothPointsX - 1; i++) {
			*e++ = i + j * m_clothPointsX;
			*e++ = 1 + i + j * m_clothPointsX;
		}
	}

	for (int i = 0; i < m_clothPointsX; i++) {
		for (int j = 0; j < m_clothPointsY - 1; j++) {
			*e++ = i + j * m_clothPointsX;
			*e++ = m_clothPointsX + i + j * m_clothPointsX;
		}
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


	return EXIT_SUCCESS;
}

int TransformFeedback::end() {
	glBindVertexArray(0);
	glUseProgram(0);

	glDeleteVertexArrays(2, m_vao);
	glDeleteBuffers(5, m_vbo);
	glDeleteProgram(update_program);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int TransformFeedback::render() {
	/* Clear */
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Update Part */
	glUseProgram(update_program);

	// Turn off the rasterization
	glEnable(GL_RASTERIZER_DISCARD);

	int iterationsPerFrame = 16;
	for (int i = iterationsPerFrame; i != 0; --i) {
		glBindVertexArray(m_vao[m_iterationIndex & 1]);
		glBindTexture(GL_TEXTURE_BUFFER, m_tbo[m_iterationIndex & 1]);
		m_iterationIndex++;

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_vbo[POS_A + (m_iterationIndex & 1)]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, m_vbo[VEL_A + (m_iterationIndex & 1)]);
		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, m_clothPointsTotal);
		glEndTransformFeedback();
	}
	// Turn on the rasterization
	glDisable(GL_RASTERIZER_DISCARD);


	/* Rendering Part */

	glUseProgram(rendering_program);
	glBindVertexArray(m_vao[1]);

	// Draw Points
	glPointSize(4.0f);
	glDrawArrays(GL_POINTS, 0, m_clothPointsTotal);

	// Draw Lines
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	int connectionsTotal = (m_clothPointsX - 1) * m_clothPointsY + (m_clothPointsY - 1) * m_clothPointsX;
	glDrawElements(GL_LINES, connectionsTotal * 2, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glUseProgram(0);

	return EXIT_SUCCESS;
}

int TransformFeedback::update(const double dt) {
	deltaTime = dt;
	time += deltaTime;


	return EXIT_SUCCESS;
}

void load_shader(GLuint& m_updateProgram) {
	char buffer[1024];

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	Helper::loadShader("feedback_update.vert", &vs);

	/*GLuint m_updateProgram;*/
	m_updateProgram = glCreateProgram();

	glAttachShader(m_updateProgram, vs);

	static const char* tf_varyings[] =
	{
		"tf_position_mass",
		"tf_velocity"
	};

	glTransformFeedbackVaryings(m_updateProgram, 2, tf_varyings, GL_SEPARATE_ATTRIBS);
	glLinkProgram(m_updateProgram);

	glGetShaderInfoLog(vs, 1024, NULL, buffer);
	glGetProgramInfoLog(m_updateProgram, 1024, NULL, buffer);

	glDeleteShader(vs);
}