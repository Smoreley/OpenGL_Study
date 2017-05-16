#include "Progbase.h"
#include "SimpleTexture.h"
#include "Helper.h"

// Fill-out data with texture info
void generate_texture(float *data, int width, int height) {
	int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}	
};

int SimpleTexture::start() {
	std::cout << "Texture Demo Program" << std::endl;

	rendering_program = Helper::compileShaders("simple.vert", "multi_texture.frag");
	
	// Vertex Array Object (holds attributes for vertexes)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::plane_vp), Helper::plane_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	static GLfloat vertex_coords[]{
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	// Tex-coords
	glGenBuffers(1, &coord_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_coords), vertex_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	// Generate Texture
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256);
	
	//// Define some data to upload to the texture
	//float *data = new float[256 * 256 * 4];
	//generate_texture(data, 256, 256);

	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA, GL_FLOAT, data);
	//delete[] data;

	glActiveTexture(GL_TEXTURE0);
	texture = Helper::createTexture("assets/tempor.dds");

	// Load texture function
	glActiveTexture(GL_TEXTURE1);
	texture_two = Helper::createTexture("assets/owltest.dds");
	

	// Enable
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	time = 0;
	return EXIT_SUCCESS;
};

int SimpleTexture::end() {
	glUseProgram(0);

	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &texture_two);

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &coord_buffer);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
};

int SimpleTexture::render() {
	double frameTime = time;

	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	glClearBufferfv(GL_COLOR, 0, clear_color);

	glUseProgram(rendering_program);

	GLuint time_loc = glGetUniformLocation(rendering_program, "time");
	glUniform1f(time_loc, frameTime);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	return EXIT_SUCCESS;
};

int SimpleTexture::update(double dtime) {
	deltaTime = dtime;
	time += deltaTime;

	return EXIT_SUCCESS;
}