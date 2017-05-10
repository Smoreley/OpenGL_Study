#include "Progbase.h"
#include "FlyingCamera.h"
#include "Helper.h"

int FlyingCamera::start() {
	std::cout << "Flying Camera Demo" << std::endl;

	// Program
	rendering_program = Helper::compileShaders("camera.vert", "depthvisualization.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Uniforms
	uniform_block_location = glGetUniformBlockIndex(rendering_program, "TransformBlock");

	mv_location = glGetUniformLocation(rendering_program, "u_mv_matrix");
	proj_location = glGetUniformLocation(rendering_program, "u_proj_matrix");
	view_location = glGetUniformLocation(rendering_program, "u_view_matrix");

	// Cube Vertex
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	time = 0;
	angle = (180.0f * glm::pi<float>()) / 180.0f;		// Convert Degrees to radians for start facing direction
	turningSpeed = 3.0f;								// How fast to turn
	walkSpeed = 4.0f;									// How fast to move forward
	camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);			// Camera position point
	camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	grid = new bool[grid_size*grid_size];

	// Populate grid
	for (int i = 0; i < grid_size*grid_size; i++) {

		if(rand()%100 > 50)
			grid[i] = true;
		else 
			grid[i] = false;
	}

	return EXIT_SUCCESS;
}

int FlyingCamera::end() {
	glUseProgram(0);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	// Delete the grid
	delete[] grid;

	return EXIT_SUCCESS;
}

int FlyingCamera::render() {
	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// TODO: Implement Rendering code

	glUseProgram(rendering_program);

	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

	// View
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

	// Display the Grid
	for (int i = 0; i < grid_size * grid_size; i++) {
		if (grid[i] == true) {
			glm::mat4 mv = glm::mat4(1.0f);
			mv = glm::translate(mv, glm::vec3(i%grid_size, 0, glm::floor(i / grid_size)));

			glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv));
			glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
		}
	}

	//for (int i = 0; i < 80; i++) {
	//	glm::mat4 mv = glm::mat4(1.0f);
	//	mv = glm::translate(mv, glm::vec3( (i%7) * glm::sin(i), (i%3), 4.0 * glm::sin(i/3.0f) ));
	//	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv));

	//	glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
	//}

	return EXIT_SUCCESS;
}

int FlyingCamera::update(const double dtime) {
	deltaTime = dtime;
	time += deltaTime;
	
	// Rotation
	if (bmap.rot_left) {
		angle += deltaTime * turningSpeed;
	}

	if (bmap.rot_right) {
		angle -= deltaTime * turningSpeed;
	}

	camera_forward = glm::vec3(sin(angle), 0.0f, cos(angle));
	camera_forward = glm::normalize(camera_forward);

	if (bmap.left)
		camera_pos += glm::normalize(glm::cross(camera_forward, camera_up));
	if (bmap.right)
		camera_pos -= glm::normalize(glm::cross(camera_forward, camera_up));

	if (bmap.up)
		camera_pos += camera_forward * glm::vec3(deltaTime * walkSpeed);
	if (bmap.down)
		camera_pos -= camera_forward * glm::vec3(deltaTime * walkSpeed);

	view = glm::lookAt(camera_pos, camera_pos + camera_forward, camera_up);


	// Crazy math function Test (constant, linear, and quadratic fall-off)
	//float a = 0, b = 1, c = 0;
	//float dist = time;
	//float res = glm::sqrt(1.0f / (a + b * dist + c * glm::pow(dist, 2)));
	//std::cout << "Result is: " << res << std::endl;

	return EXIT_SUCCESS;
}