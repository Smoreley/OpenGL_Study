#include "TexturedCube.h"
#include "Helper.h"

int TexturedCube::start() {
	std::cout << "Cube Texture Demo" << std::endl;

	rendering_program = Helper::compileShaders("transform.vert", "texture.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Trans
	mov_loc = glGetUniformLocation(rendering_program, "u_mv_matrix");
	proj_loc = glGetUniformLocation(rendering_program, "u_proj_matrix");
	
	// Model
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	std::cout << std::rand() << std::endl;

	// Colors
	static GLfloat vertex_colors[200];
	std::fill_n(vertex_colors, 200, (std::rand() % 100)/100.0f );

	// Change some of the RGBA values to get different colors
	for (int i = 0; i < 200; i += 4) {
		*(vertex_colors + i) = i % 16 / 16.0f;
		*(vertex_colors + i + 1) = i % 64 / 64.0f;
		*(vertex_colors + i + 2) = i % 32 / 32.0f;
	}

	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	static GLfloat vertex_coords[]{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		//
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
	};

	// Tex-coords
	glGenBuffers(1, &coord_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_coords), vertex_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	// Texture
	glActiveTexture(GL_TEXTURE0);
	cube_tex = Helper::createTexture("assets/owltest.dds");

	// Capabilities
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Depth test for multiple objects so further object are occluded
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	time = 0;
	return EXIT_SUCCESS;
}

int TexturedCube::end() {
	glUseProgram(0);
	
	glDeleteTextures(1, &cube_tex);

	glDeleteBuffers(0, &vertex_buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int TexturedCube::render() {
	static const GLfloat clear_color[] = { 0.415, 0.568, 0.431, 1.0 };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// Set what program to use
	glUseProgram(rendering_program);

	// Projection Calculation
	static const float aspect = 1280.0f / 720.0f;
	glm::mat4 proj_matrix = glm::perspective(1.0472f, aspect, 0.1f, 100.0f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj_matrix));

	// Movement 
	glm::mat4 mv_matrix = glm::mat4(1.0f);
	mv_matrix = glm::translate(mv_matrix, glm::vec3(0.0f, 0.0f, -2.0f));
	mv_matrix = glm::rotate(mv_matrix, glm::sin((float)time) * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(mov_loc, 1, GL_FALSE, glm::value_ptr(mv_matrix));

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);

	glPointSize(16.0f);
	glDrawArrays(GL_POINTS, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);

	return EXIT_SUCCESS;
}

int TexturedCube::update(double dtime) {
	deltaTime = dtime;
	time += deltaTime;
	double frameTime = time;

	return EXIT_SUCCESS;
}