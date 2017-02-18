#include "stdafx.h"

// Custom
#include "progbase.h"
#include "SimpleTriangle.h"
#include "SimpleCube.h"

// Window
static const GLint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
static const char *WINDOW_TITLE = "The Study";
static double currentTime = 0, previousTime = 0;

// Study
Progbase* currentStudyProgram;
std::vector<Progbase*> studyContainer;
int studyLocation = 0;
void next(); // Needed to define before use

void createWindow(GLint w, GLint h, char &name) {

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		std::cout << "N WAS PRESSED" << std::endl;
		next();
	}
	else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		std::cout << "B was pressed" << std::endl;
	}
}

// Next study
void next() {
	currentStudyProgram->end();
	studyLocation++;
	studyLocation %= studyContainer.size();
	currentStudyProgram = studyContainer[studyLocation];
	currentStudyProgram->start();
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

	// Custom print versions
	printVersion();

	// Initialize my program
	/*Progbase* studyProgram = new SimpleTriangle();*/
	//studyProgram->start();
	studyContainer.push_back(new SimpleTriangle());
	studyContainer.push_back(new SimpleCube());

	//Progbase* studys[] = { new SimpleTriangle(), new SimpleTriangle() };
	currentStudyProgram = studyContainer[0];
	currentStudyProgram->start();

	// Keyboard input
	glfwSetKeyCallback(window, key_callback);

	// Loop until user closes window
	while (!glfwWindowShouldClose(window)) {
		previousTime = currentTime;
		currentTime = glfwGetTime();
		double delta = currentTime - previousTime;

		currentStudyProgram->render(delta);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Clean up study programs
	currentStudyProgram->end();
	for (int i = 0; i < studyContainer.size(); i++) {
		delete studyContainer[i];
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}