#pragma once
#include <GLFW\glfw3.h>

#include <string>
#include <sstream>
#include <chrono>
#include <thread>

class FpsManager
{
public:
	
	~FpsManager();

	// All the constructors
	FpsManager() : FpsManager(DEFAULT_FPS) {};
	FpsManager(int targetFps) : FpsManager(targetFps, DEFAULT_REPORT_INTERVAL) {};
	FpsManager(int targetFps, float reportInterval) : FpsManager(targetFps, reportInterval, "NONE") {};
	FpsManager(int targetFps, float reportInterval, std::string windowTitle);

	// Get
	bool getVerbose() { return verbose;  }
	int getTargetFps() { return targetFps; }
	double getFrameDuration() { return frameDuration;  }

	// Set
	void setTargetFps(float targetFps) { 
		this->targetFps = targetFps;
		targetFrameDuration = 1.0f / targetFps;
	}

	void setReportInterval(float reportInterval) { this->reportInterval = reportInterval; }
	void setWindow(GLFWwindow *window) { this->window = window; }

	double enforceFPS();
	double reportFPS();

private:

	// Limit the min-max target FPS values to relatively sane ones
	const double MIN_TARGET_FPS = 20.0;
	const double MAX_TARGET_FPS = 120.0;
	const float DEFAULT_REPORT_INTERVAL = 1;
	const int DEFAULT_FPS = 60;

	double frameStartTime;
	double frameEndTime;
	double frameDuration;		// How many miliseconds between the last frame and this frame

	double targetFps;			// Desired FPS to run at
	double currentFps;			// Current FPS value
	int frameCount;				// How many frames have been drawn

	double targetFrameDuration;	// How many milliseconds each frame should take to hit a target FPS value
	double sleepDuration;		// How long to sleep if exceeding the target frame rate duration

	double lastReportTime;		// The timestamp of when we last reported
	float reportInterval;		// How often to update the FPS value

	std::string windowTitle;	// Window title to update view GLFW

	bool verbose;				// output FPS details to the console or update the window
	bool console_print;
	bool title_print;

	GLFWwindow* window;			// Pointer to window


};

// Constructor
FpsManager::FpsManager(int targetFps, float reportInterval, std::string windowTitle) {
	setTargetFps(targetFps);
	frameCount = 0;
	currentFps = 0.0;
	sleepDuration = 0.0;
	frameStartTime = glfwGetTime();
	frameEndTime = frameStartTime + 1;
	frameDuration = 1;
	lastReportTime = frameStartTime;
	this->reportInterval = reportInterval;
	this->windowTitle = windowTitle;
	verbose = true;

	console_print = false;
	title_print = true;
}

FpsManager::~FpsManager()
{
}

double FpsManager::reportFPS() {
	// Get the current time
	frameEndTime = glfwGetTime();

	// Calculate how long it's been since the frameStartTime was set
	frameDuration = frameEndTime - frameStartTime;

	if (reportInterval != 0.0f) {
		// Calculate and display the FPS every specified time interval
		if ((frameEndTime - lastReportTime) > reportInterval) {
			// Update the last report time to be now
			lastReportTime = frameEndTime;

			// Calculate the FPS as the number of frames divided by the interval in seconds
			currentFps = (double)frameCount / reportInterval;
			double currentFpms = 1000.0f / frameCount;

			// Reset the frame counter to 1 
			frameCount = 1;

			if (console_print) {
				std::cerr << "FPS: " << currentFps << std::endl;
			}

			if (title_print) {
				// If the user specified a window title to append the FPS value to
				if (windowTitle != "NONE") {
					// Convert the fps value into a string using an output stringstream
					std::ostringstream stream;
					stream << currentFps;
					std::string fpsString = stream.str();

					stream.str("");
					stream << currentFpms;
					std::string msString = stream.str();

					// Append the FPS value to the window title details
					std::string tempWindowTitle = windowTitle + " | FPS: " + fpsString + " | ms: " + msString;

					// Convert the new window title to a c_str and set it
					const char* pszConstString = tempWindowTitle.c_str();
					glfwSetWindowTitle(window, pszConstString);

				}
			}
		}
		else {
			// Fps calculation time interval hasn't elapsed yet? 
			++frameCount;
		}

	}	// End of report interval

	// Reset the frame start time
	frameStartTime = glfwGetTime();

	// Pass back our total frame duration
	return frameDuration + (frameStartTime - frameEndTime);
}

double FpsManager::enforceFPS() {
	// Get the current time
	frameEndTime = glfwGetTime();

	// Calculate how long it's been since the frameStartTime was set
	frameDuration = frameEndTime - frameStartTime;

	if (reportInterval != 0.0f) {
		// Calculate and display the FPS every specified time interval
		if ((frameEndTime - lastReportTime) > reportInterval) {
			// Update the last report time to be now
			lastReportTime = frameEndTime;

			// Calculate the FPS as the number of frames divided by the interval in seconds
			currentFps = (double)frameCount / reportInterval;
			double currentFpms = 1000.0f / frameCount;

			// Reset the frame counter to 1 
			frameCount = 1;

			if (console_print) {
				std::cerr << "FPS: " << currentFps << std::endl;
			}

			if (title_print) {
				// If the user specified a window title to append the FPS value to
				if (windowTitle != "NONE") {
					// Convert the fps value into a string using an output stringstream
					std::ostringstream stream;
					stream << currentFps;
					std::string fpsString = stream.str();

					stream.str("");
					stream << currentFpms;
					std::string msString = stream.str();

					// Append the FPS value to the window title details
					std::string tempWindowTitle = windowTitle + " | FPS: " + fpsString + " | ms: " + msString;

					// Convert the new window title to a c_str and set it
					const char* pszConstString = tempWindowTitle.c_str();
					glfwSetWindowTitle(window, pszConstString);

				}
			}
		}
		else {
			// Fps calculation time interval hasn't elapsed yet? 
			++frameCount;
		}

	}	// End of report interval

	// Calculate how long we should sleep for to stick to the target frame rate
	sleepDuration = (targetFrameDuration - frameDuration);
	//std::cout << "Time 2: " << targetFrameDuration << " " << frameDuration << " Outcome: " <<
	//	sleepDuration		
	//	<< std::endl;

	int stall = targetFps - (glfwGetTime() - frameStartTime);
	//std::cout << "Stall 2: " << stall << std::endl;

	//if (sleepDuration > 0.0) {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(
	//		(int) (stall)
	//	));
	//}


	// Reset the frame start time
	frameStartTime = glfwGetTime();

	// Pass back our total frame duration
	return frameDuration + (frameStartTime - frameEndTime);
}