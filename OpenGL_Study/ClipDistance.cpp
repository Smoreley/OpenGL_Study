#include "Progbase.h"
#include "ClipDistance.h"

#include "Model.h"
#include "Camera.h"

#include "Helper.h"

int ClipDistance::start() {
	std::cout << "ClipDistance demo" << std::endl;

	rendering_program = Helper::compileShaders("clip.vert", "clip.frag");

	// Get Uniform locations
	m_modelView_location = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_view_location = glGetUniformLocation(rendering_program, "u_view_matrix");
	//m_projectionUniform = glGetUniformLocation(rendering_program, "u_proj_matrix");
	m_clipPlane_location = glGetUniformLocation(rendering_program, "u_clip_plane");

	// Load Model
	m_pModel = new Model("assets/teapot.obj");
	//m_pModel = new Model("assets/models/cat.obj");
	

	float distanceFromModel = 50;
	// Camera Setup
	m_pCamera = new Camera();
	m_pCamera->SetPosition(vec3(distanceFromModel, 70, distanceFromModel));
	m_pCamera->SetUpVector(vec3(0.0f, 5.0f, 0.0f));
	m_pCamera->SetLookAtTarget(vec3(0.0, 25.0f, 0.0f));
	m_pCamera->SetFarClipPlane(500.0f);

	// Vertex Arrays
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Enables
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CLIP_DISTANCE0);

	// Alpha Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return EXIT_SUCCESS;
}

int ClipDistance::end() {

	delete m_pModel;
	delete m_pCamera;


	glBindVertexArray(0);
	glUseProgram(0);

	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int ClipDistance::render() {
	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);


	// Render
	glUseProgram(rendering_program);
	glBindVertexArray(m_vao);

	// Camera
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(m_pCamera->GetMatrix()));

	// Model position
	mat4 mv = glm::mat4(1.0f);
	mv = glm::rotate(mv, (float)m_time/5.0f, vec3(0, 1.0, 0));
	//mv = glm::rotate(mv, vec3(0, 0.0, 0.0f));
	glUniformMatrix4fv(m_modelView_location, 1, GL_FALSE, glm::value_ptr(mv));

	// ClipPlane Normal Vector
	glUniform4f(m_clipPlane_location, cosf(m_time), 0.0, sinf(m_time), 0.0);

	m_pModel->Draw();

	glUseProgram(0);

	return EXIT_SUCCESS;
}

int ClipDistance::update(const double dtime) {
	m_deltaTime = dtime;
	m_time += m_deltaTime;

	return EXIT_SUCCESS;
}