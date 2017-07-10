#pragma once

// Chapter 7 - TransformFeedback
class TransformFeedback : public Progbase {
public:
	int start();
	int end();
	int render();
	int update(const double);


private:
	double deltaTime;
	double time;

	GLuint update_program;

	GLuint m_vao[2];			// Vertex Array Object (Stores the state)
	GLuint m_vbo[5];			// Vertext Buffer Object
	GLuint m_ibo;				// Index Buffer Object

	GLuint m_tbo[2];			// Texture Buffer Object


	GLuint m_iterationIndex;

	// Uniforms
	GLuint m_modelViewLocation;
	GLuint m_projectionLocation;
	GLuint m_viewLocation;

	int m_clothPointsTotal;
	int m_clothPointsX{ 20 };
	int m_clothPointsY{ 20 };

};