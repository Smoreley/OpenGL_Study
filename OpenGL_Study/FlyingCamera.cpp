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
	angle = 1;
	turningSpeed = 3.0f;
	walkSpeed = 4.0f;
	camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);			// Camera position point
	camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	return EXIT_SUCCESS;
}

int FlyingCamera::end() {
	glUseProgram(0);

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int FlyingCamera::render() {
	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// TODO: Implement Rendering code

	glUseProgram(rendering_program);

	// Projection Matrix
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

	for (int i = 0; i < 20; i++) {
		glm::mat4 mv = glm::mat4(1.0f);
		mv = glm::translate(mv, glm::vec3(i%7, i%2, -i * glm::abs(sin(time/4.0f))));
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv));


		glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
	}

	return EXIT_SUCCESS;
}

int FlyingCamera::update(double dtime) {
	deltaTime = dtime;
	time += deltaTime;
	

	// Rotation
	if (bmap.rot_left) {
		angle += deltaTime;
	}

	if (bmap.rot_right) {
		angle -= deltaTime;
	}

	camera_forward = glm::vec3(sin(angle), 0.0f, cos(angle));
	camera_forward = glm::normalize(camera_forward);

	if(bmap.left)
		camera_pos += glm::normalize(glm::cross(camera_forward, camera_up)) * glm::vec3(deltaTime * turningSpeed);
	if (bmap.right)
		camera_pos -= glm::normalize(glm::cross(camera_forward, camera_up)) * glm::vec3(deltaTime * turningSpeed);

	if (bmap.up)
		camera_pos += camera_forward * glm::vec3(deltaTime * walkSpeed);
	if (bmap.down)
		camera_pos -= camera_forward * glm::vec3(deltaTime * walkSpeed);


	//view = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::lookAt(camera_pos, camera_pos + camera_forward, camera_up);

	//view = glm::rotate(view, angle.y, glm::vec3(0.0, 1.0f, 0.0f));
	
	return EXIT_SUCCESS;
}