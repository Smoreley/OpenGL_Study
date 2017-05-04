#pragma once
#include "stdafx.h"

#include <fstream>
#include <sstream>

#include "PrebuiltPrimitives.h"

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

	// Create load and create texture
	static GLuint createTexture(const char* filename) {

		// Load texture from file
		gli::texture tex = gli::load(filename);

		// early bail-out if texture empty
		if (tex.empty())
			return 0;

		// GL translation class to convert GLI enums into OpenGL
		gli::gl GL(gli::gl::PROFILE_GL33);

		// Convert GLI formats into OpenGL texture formats
		gli::gl::format const tex_format = GL.translate(tex.format(), tex.swizzles());
		// Convert GLI targets into OpenGL texture targets
		GLenum tex_target = GL.translate(tex.target());

		// Name for Texture, gen, and bind
		GLuint tex_name = 0;
		glGenTextures(1, &tex_name);
		glBindTexture(tex_target, tex_name);

		// Dimensions of texture
		glm::tvec3<GLsizei> const tex_extent(tex.extent());

		// Set Parameters
		glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		// Specifies the index of the lowest defined mipmap level
		glTexParameteri(tex_target, GL_TEXTURE_BASE_LEVEL, 0);
		// Sets the index of highest mipmap level
		glTexParameteri(tex_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(tex.levels() - 1));
		// Specifying the order of the color components 
		glTexParameteriv(tex_target, GL_TEXTURE_SWIZZLE_RGBA, &tex_format.Swizzles[0]);

		// Make room in storage
		glTexStorage2D(tex_target, static_cast<GLint>(tex.levels()), tex_format.Internal, tex_extent.x, tex_extent.y);

		GLint tex_level = 0;

		//std::cout << "TEX LEVELS: " << tex.levels() << std::endl;

		if (gli::is_compressed(tex.format())) {

			//for (std::size_t Level = 0; Level < tex.levels(); ++Level) {
			//	glm::tvec3<GLsizei> Extent(tex.extent(Level));
			//	glCompressedTexSubImage2D(
			//		tex_target, static_cast<GLint>(Level), 0, 0, tex_extent.x, tex_extent.y,
			//		tex_format.Internal, static_cast<GLsizei>(tex.size(Level)), tex.data(0, 0, Level)
			//	);
			//}

			glCompressedTexSubImage2D(
				tex_target,
				tex_level,
				0,
				0,
				tex_extent.x,
				tex_extent.y,
				tex_format.Internal,
				tex.size(tex_level),
				tex.data(0, 0, tex_level)
			);
		}
		else {
			glTexSubImage2D(tex_target, tex_level, 0, 0,
				tex_extent.x, tex_extent.y,
				tex_format.Internal, tex_format.Type, tex.data(0, 0, 0)
			);

			std::cout << "This image is not compressed" << std::endl;
		}

		return tex_name;
	} // End of createTexture
}