#pragma once
#include <GL/glew.h>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "QuickPrimitives.h"

namespace Helper {

	// Given shaderHandle 
	static int loadShader(const char* fileName, GLuint* shaderHandle) {
		// Open File
		std::ifstream file;
		file.open(fileName, std::ios::in);

		// File found
		if (!file) {
			std::cerr << "Was unable to locate file: " << fileName << std::endl;
			return EXIT_FAILURE;
		}

		// File was loaded
		std::stringstream buffer;
		buffer << file.rdbuf();

		std::string sourceString = buffer.str();
		const char* shaderSource = sourceString.c_str();

		// File has characters
		if (file.seekg(0, file.end).tellg() <= 0) {
			std::cerr << "Shader file is empty: " << fileName << std::endl;
			return EXIT_FAILURE;
		}

		// Close file
		file.close();

		// Upload code to OpenGL
		glShaderSource(*shaderHandle, 1, &shaderSource, NULL);

		// Compile shader
		glCompileShader(*shaderHandle);

		// Check if shader compiled
		GLint compiled;
		glGetShaderiv(*shaderHandle, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cerr << "Shader was unable to compile: " << fileName << std::endl;

			GLint logSize;
			glGetShaderiv(*shaderHandle, GL_INFO_LOG_LENGTH, &logSize);

			//std::vector<GLchar> errorLog(logSize);
			GLchar* errorLog = new char[logSize];
			glGetShaderInfoLog(*shaderHandle, logSize, &logSize, &errorLog[0]);

			std::cerr << errorLog << std::endl;
			delete [] errorLog;

			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	// Given shaders compile them and create a program
	static GLuint compileShaders(const char* vsfilename, const char* fsfilename) {
		
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		Helper::loadShader(vsfilename, &vs);

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		loadShader(fsfilename, &fs);

		// Create program 
		GLuint program = glCreateProgram();

		// Attach shaders to program
		glAttachShader(program, vs);
		glAttachShader(program, fs);

		// Link all attached shaders to the program object together
		glLinkProgram(program);

		glDetachShader(program, vs);
		glDetachShader(program, fs);

		// Delete the shaders, since the program has them now
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}