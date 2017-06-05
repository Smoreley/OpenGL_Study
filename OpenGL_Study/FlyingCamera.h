#pragma once

class Camera;

class FlyingCamera : public  Progbase {
public:
	int start();
	int end();
	int render();
	int update(const double);

private:
	double deltaTime;
	double time;

	GLuint vao;
	GLuint vbo;

	// Uniforms
	GLuint mv_location;
	GLuint proj_location;
	GLuint view_location;

	GLuint uniform_block_location;

	struct transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 projection;
	};

	transform my_trans;

	// Camera
	glm::vec3 camera_pos;
	glm::vec3 camera_forward;
	glm::vec3 camera_up;
	glm::mat4 view;
	float angle;
	float walkSpeed;
	float turningSpeed;

	// Grid
	const int grid_size = 20;
	//bool grid[grid_size][grid_size];
	bool* grid;

	// Camera
	Camera* m_camera;
	
};