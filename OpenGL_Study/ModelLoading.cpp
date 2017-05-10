#include "Progbase.h"
#include "ModelLoading.h"
#include "Helper.h"

int ModelLoading::start() {
	std::cout << "Model Loading Demo" << std::endl;

	// Load object file
	m_fileName = "assets/models/teapot.obj";
	loadFile(m_fileName);


	// Rendering Program
	rendering_program = Helper::compileShaders("simple.vert", "simplecolor.frag");




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