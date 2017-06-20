#include "Progbase.h"
#include "Model.h"
#include "ModelLoading.h"
#include "Helper.h"

int ModelLoading::start() {
	std::cout << "Model Loading Demo" << std::endl;

	//// Load object file
	m_fileName = "assets/teapot.obj";
	loadFile(m_fileName);

	// Rendering Program
	rendering_program = Helper::compileShaders("model.vert", "model.frag");


	// Load Model
	m_pModel_tea = new Model("assets/teapot.obj");
	m_pModel = new Model("assets/spider.obj");

	// Get Uniform Locations
	m_UniformLocation.mv = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_UniformLocation.proj = glGetUniformLocation(rendering_program, "u_proj_matrix");
	m_UniformLocation.view = glGetUniformLocation(rendering_program, "u_view_matrix");
	m_UniformLocation.time = glGetUniformLocation(rendering_program, "u_time");


	// Vertex Arrays
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glEnableVertexAttribArray(0);

	// Enable
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return EXIT_SUCCESS;
}

int ModelLoading::end() {
	glUseProgram(0);

	delete m_pModel;
	delete m_pModel_tea;

	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int ModelLoading::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	GLfloat radius = 45.0f;
	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(radius * cos(time), 15, radius * sin(time)),		// Camera Position
		glm::vec3(0.0f, 1.0f , 0.0f),								// Look at target
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	glm::mat4 model_view;
	model_view = glm::translate(model_view, glm::vec3(0.0f, 0.0f, 0.0f));
	model_view = glm::scale(model_view, glm::vec3(0.2f, 0.2f, 0.2f));

	glUniformMatrix4fv(m_UniformLocation.proj, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(m_UniformLocation.view, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(m_UniformLocation.mv, 1, GL_FALSE, glm::value_ptr(model_view));


	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);

	// Draw Model
	m_pModel->Draw();

	// Draw Teapot
	model_view = glm::translate(model_view, glm::vec3(0.0f, 40.0f, 0.0f));
	glUniformMatrix4fv(m_UniformLocation.mv, 1, GL_FALSE, glm::value_ptr(model_view));
	m_pModel_tea->Draw();

	glUseProgram(0);
	return EXIT_SUCCESS;
}

int ModelLoading::update(const double dt) {
	deltaTime = dt;
	time += deltaTime;

	return EXIT_SUCCESS;
}

uint8 ModelLoading::loadFile(const std::string &fileName) {
	std::fstream file;
	file.open(fileName);

	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << m_fileName << std::endl;
		return EXIT_FAILURE;
	}
}