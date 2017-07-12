#pragma once

// Chapter 8 - Tessellation Terrain
class TessellationTerrain : public Progbase {
public:
	int start();
	int end();
	int render();
	int update(const double);

private:
	double m_deltaTime;
	double m_time;

	GLuint m_vao;				// Vertex Array Object (Stores the state);
	GLuint m_vbo;				// Vertex Buffer Object

	GLuint m_tbo[2];			// Texture Buffer Object


	// Uniforms
	GLuint m_modelView;
	GLuint m_projection;
	GLuint m_view;
	GLuint m_mvp;
	GLuint m_dmapDepth;


	// Options
	bool m_wireframe;


	// Helper Functions
	//void Add_Shader(const GLuint&, GLenum, const char*);
	void load_shader(GLuint& prog);
};