#include "stdafx.h"

#include <thread>
#include <chrono>

#include "Timer.h"

// Custom
#include "progbase.h"
#include "SimpleTriangle.h"
#include "SimpleCube.h"
#include "SimpleTransform.h"
#include "SimpleTexture.h"
#include "TexturedCube.h"
#include "MultiCubeRendering.h"
#include "VertexIndexing.h"
#include "GrassInstanced.h"
#include "FlyingCamera.h"

// Window
static GLint RES_MULTI = 1;
static const GLint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
static const char *WINDOW_TITLE = "The Study";

static int monitor_res_width, monitor_res_height;

// FrameRate
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// Study
Progbase* currentStudyProgram;
std::vector<Progbase*> studyContainer;
int studyLocation = 0;
void next(); // Needed to define before use
void back();

void createWindow(GLint w, GLint h, char &name) {

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		std::cout << "N WAS PRESSED" << std::endl;
		next();
	}
	else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		std::cout << "B was pressed" << std::endl;
		//back();
	}

	// Hit escape key to exit window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Resize
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		RES_MULTI = (RES_MULTI%5) + 1;
		GLint new_window_width = monitor_res_width / RES_MULTI;
		GLint new_window_height = monitor_res_height / RES_MULTI;

		glfwSetWindowSize(window, new_window_width, new_window_height);
		glViewport(0, 0, new_window_width, new_window_height);
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

void back() {
	currentStudyProgram->end();
	studyLocation--;
	studyLocation %= studyContainer.size();
	currentStudyProgram = studyContainer[studyLocation];
	currentStudyProgram->start();
}

void printVersion() {
	std::cout << "GLFW: " << glfwGetVersionString() << std::endl;
	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
}

void printWindowInfo() {
	int phys_width, phys_height;
	glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &phys_width, &phys_height);

	int res_width, res_height;
	const GLFWvidmode *mode;
	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	res_width = mode->width;
	res_height = mode->height;


	monitor_res_width = mode->width;
	monitor_res_height = mode->height;

	//glfwGetWindowSize(window, &width, &height);
	std::cout << "Window [Physical: " << phys_width << "/" << phys_height <<
		", Resolution: " << res_width << "/" << res_height << "]" << std::endl;
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

	// Print window Info
	printWindowInfo();

	// Initialize my programs
	//studyContainer.push_back(new SimpleTriangle());
	//studyContainer.push_back(new SimpleCube());
	//studyContainer.push_back(new SimpleTransform());
	//studyContainer.push_back(new SimpleTexture());
	//studyContainer.push_back(new TexturedCube());
	//studyContainer.push_back(new MultiCubeRendering());
	//studyContainer.push_back(new VertexIndexing());
	studyContainer.push_back(new GrassInstanced());
	//studyContainer.push_back(new FlyingCamera());

	// Set current running program and start it
	currentStudyProgram = studyContainer[0];
	currentStudyProgram->start();

	// Keyboard input
	glfwSetKeyCallback(window, key_callback);

	// Performance calculation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	Timer myTimer;

	// Loop until user closes window
	while (!glfwWindowShouldClose(window)) {
		myTimer.updateTime();

		// Performance Calculation
		nbFrames++;
		if (glfwGetTime() - lastTime >= 1.0) {
			std::cerr << ((glfwGetTime() - lastTime) * 1000.0) / double(nbFrames) << "\tms/frames" << std::endl;
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Run study program
		currentStudyProgram->update();

		// Render
		currentStudyProgram->render();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		// Sleep if we have time to
		//double startTime = myTimer.getTime();
		//if (startTime + SCREEN_TICKS_PER_FRAME > glfwGetTime()) {
		//	//SDL_Delay((startTime + SCREEN_TICKS_PER_FRAME) - glfwGetTime());
		//	std::this_thread::sleep_for(std::chrono::milliseconds(
		//		(int)((startTime + SCREEN_TICKS_PER_FRAME) - glfwGetTime())
		//	));
		//}
	}

	// Clean up study programs
	currentStudyProgram->end();
	for (int i = 0; i < studyContainer.size(); i++) {
		delete studyContainer[i];
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}