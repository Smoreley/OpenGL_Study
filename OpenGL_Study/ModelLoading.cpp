#include "Progbase.h"
#include "ModelLoading.h"
#include "Helper.h"
#include "Mesh.h"

int ModelLoading::start() {
	std::cout << "Model Loading Demo" << std::endl;

	// Load object file
	m_fileName = "assets/models/teapot.obj";
	loadFile(m_fileName);


	// Rendering Program
	rendering_program = Helper::compileShaders("simple.vert", "simplecolor.frag");


	// Load Model
	tempor_model("some.obj");


	// Get Uniform Locations
	m_UniformLocation.mv = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_UniformLocation.proj = glGetUniformLocation(rendering_program, "u_proj_matrix");
	m_UniformLocation.view = glGetUniformLocation(rendering_program, "u_view_matrix");
	m_UniformLocation.time = glGetUniformLocation(rendering_program, "u_time");

	// Enable
	glEnable(GL_DEPTH_TEST);

	return EXIT_SUCCESS;
}

int ModelLoading::end() {
	glUseProgram(0);


	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int ModelLoading::render() {
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(rendering_program);

	GLfloat radius = 180.0f;
	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(radius, 150.0f, radius),
		glm::vec3(0.0f, -20.0f, 0.0f),
		glm::vec3(9.0f, 1.0f, 0.0f)
	);

	

	// Rendering code



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

	if (file.is_open()) {
		std::cerr << "Unable to open file: " << m_fileName << std::endl;
		return EXIT_FAILURE;
	}


}