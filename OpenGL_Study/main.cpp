#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "progbase.h"
#include "SimpleTriangle.h"

static const GLint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
static const char *WINDOW_TITLE = "The Study";

static double currentTime = 0, previousTime = 0; 

void createWindow(GLint w, GLint h, char &name) {

}

void printVersion() {
	std::cout << "GLFW: " << glfwGetVersionString() << std::endl;
	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
}

int main(void) {

	// Initiate glfw
	if (GLFW_TRUE != glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	// The minimal viable version the client api must be
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	// Only the new stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window isn't re-sizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	// Create window 
	GLFWwindow* window;
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Ensure all extensions with valid entry points are exposed
	glewExperimental = GL_TRUE;

	// Initiate GLEW
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	printVersion();

	Progbase* studyProgram = new SimpleTriangle();
	studyProgram->start();

	// Loop until user closes window
	while (!glfwWindowShouldClose(window)) {
		previousTime = currentTime;
		currentTime = glfwGetTime();
		double delta = currentTime - previousTime;

		studyProgram->render(delta);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}