#include "Progbase.h"
#include "TessellationTerrain.h"
#include "Helper.h"

// Forward-dec
//void load_shader(GLuint& prog);

int TessellationTerrain::start() {
	std::cout << "Terrain Tessellation Demo" << std::endl;

	// OpenGL
	load_shader(rendering_program);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);


	// Load Textures
	glActiveTexture(GL_TEXTURE0);
	m_tbo[0] = Helper::createTexture("assets/HMap.dds");

	glActiveTexture(GL_TEXTURE1);
	m_tbo[1] = Helper::createTexture("assets/HMap.dds");

	// Uniforms
	m_modelView = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_projection = glGetUniformLocation(rendering_program, "u_proj_matrix");
	//m_view = glGetUniformLocation(rendering_program, "u_view_matrix");
	m_mvp = glGetUniformLocation(rendering_program, "u_mvp_matrix");
	m_dmapDepth = glGetUniformLocation(rendering_program, "u_dmap_depth");

	// Enables
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Set Parameters
	m_wireframe = true;

	return EXIT_SUCCESS;
}

int TessellationTerrain::end() {
	glBindVertexArray(0);
	glUseProgram(0);

	glDeleteTextures(2, m_tbo);

	glDeleteVertexArrays(1, &m_vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int TessellationTerrain::render() {

	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// Set Which Program were using
	glUseProgram(rendering_program);


	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100000.0f);

	// Model View Matrix
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, 0, 0));

	float r = sinf(m_time / 4.0f) * 15.0 +20.0;
	float h = cosf(m_time / 4.0f) * 15.0f + 20.0f;
	mv = glm::lookAt(vec3(sinf(m_time/10.0f) * r, h, cosf(m_time/10.0f) * r), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));


	// Set uniforms
	glUniformMatrix4fv(m_modelView, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(m_projection, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(m_mvp, 1, GL_FALSE, glm::value_ptr(proj * mv));
	glUniform1f(m_dmapDepth, 10.0f);	

	if (m_wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64*64);
	//glDrawArraysInstanced(GL_PATCHES, 0, 4, 32 * 32);

	// Unset program
	glUseProgram(0);

	return EXIT_SUCCESS;
}

int TessellationTerrain::update(const double dt) {
	m_deltaTime = dt;
	m_time += m_deltaTime;

	return EXIT_SUCCESS;
}


//
void TessellationTerrain::load_shader(GLuint& prog) {
	//char buffer[1024];

	// Vertex Shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	Helper::loadShader("tessTerrain.vert", &vs);

	// Tess Control Shader
	GLuint tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
	Helper::loadShader("tessTerrain.tcs", &tcs);

	// Tess Evaluation Shader
	GLuint tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
	Helper::loadShader("tessTerrain.tes", &tes);

	// Fragment Shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	Helper::loadShader("tessTerrain.frag", &fs);

	// Create Program
	prog = glCreateProgram();

	// Attach shaders to program
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);

	glAttachShader(prog, tcs);
	glAttachShader(prog, tes);

	//Add_Shader(program, GL_VERTEX_SHADER, "tessTerrain.vert");
	//Add_Shader(program, GL_FRAGMENT_SHADER, "tessTerrain.frag");
	//Add_Shader(program, GL_TESS_CONTROL_SHADER, "tessTerrain.tcs");
	//Add_Shader(program, GL_TESS_EVALUATION_SHADER, "tessTerrain.tes");

	// Link shaders to program
	glLinkProgram(prog);

	// Cleanup
	glDetachShader(prog, vs);
	glDetachShader(prog, fs);
	glDetachShader(prog, tcs);
	glDetachShader(prog, tes);

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(tcs);
	glDeleteShader(tes);
}

//void TessellationTerrain::Add_Shader(const GLuint& program, GLenum shaderType, const char* file_name) {
//
//	GLuint shader = glCreateShader(shaderType);
//	Helper::loadShader(file_name, &shader);
//	glAttachShader(program, shader);
//}