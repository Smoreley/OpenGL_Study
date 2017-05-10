#pragma once
#include <iostream>
#include <fstream>		// Full Creation
#include <assert.h>		// Asserting stuff

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct OpenGLDebugger
{

	//static char *filename;
	//static bool outputToFile;
	//static bool outputToConsole;
	//static bool appendToDebugFile;

	static void APIENTRY Callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParm) {

		// Create String
		std::string output_string;
		
		output_string += "--------------------------------\n";
		output_string += getStringForTimeStamp();
		output_string += "Source: "		+ getStringForSource(source)		+ "\n";
		output_string += "Type: "		+ getStringForType(type)			+ "\n";
		output_string += "Severity: "	+ getStringForSeverity(severity)	+ "\n";
		output_string += "Info: "		+ std::string(message)				+ "\n";
		output_string += "--------------------------------\n";

		char* filename = "OpenGLDebug";
		if (filename) {
			
			// Get file
			std::ofstream file;

			bool appendToDebugFile = true;
			if (appendToDebugFile) {
				file.open(filename);
			}
			else {
				file.open(filename+'.log', std::ios::app);		// Append to file
			}

			// Send output_string to file
			file << output_string;

			// Closing the file when we are done with it
			file.close();
		}


		// only print to console if it is very sever
		//if (severity == GL_DEBUG_SEVERITY_HIGH) {
		//	std::cout << message << std::endl;
		//}

		bool outputToConsole = true;
		if (outputToConsole) {
			std::cout << output_string;
		}

	}

	static std::string getStringForType(GLenum type) {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			return"Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "Deprecated behavior";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "Undefined behavior";
		case GL_DEBUG_TYPE_PORTABILITY:
			return "Portability issue";
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "Performance issue";
		case GL_DEBUG_TYPE_MARKER:
			return "Stream annotation";
		case GL_DEBUG_TYPE_OTHER_ARB:
			return "Other";
		default:
			assert(false);
			return "";
		}
	}

	static std::string getStringForSource(GLenum source) {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "Window system";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "Shader compiler";
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "Third party";
		case GL_DEBUG_SOURCE_APPLICATION:
			return "Application";
		case GL_DEBUG_SOURCE_OTHER:
			return "Other";
		default:
			assert(false);
			return "";
		}
	}

	static std::string getStringForSeverity(GLenum severity) {
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			return "High";
		case GL_DEBUG_SEVERITY_MEDIUM:
			return "Medium";
		case GL_DEBUG_SEVERITY_LOW:
			return "Low";
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			return "Notification";
		default:
			assert(false);
			return("");
		}
	}

	static std::string getStringForTimeStamp() {
		std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		char str[64];
		ctime_s(str, sizeof(str), &current_time);
		std::string temp = str;

		// Get rid of pesky newline character
		//for (int i = 0; i < sizeof(str) / sizeof(char); i++) {
		//	if (str[i] == '\n') {
		//		str[i] = ' ';
		//	}
		//}

		return temp;

	}

};	// End of OpenGLDebugger Class