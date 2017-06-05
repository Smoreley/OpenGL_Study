#pragma once

class Camera
{
public:
	Camera(unsigned int fov = 60, glm::vec3 pos = glm::vec3(0.0), glm::vec3 lookAtTarget = glm::vec3(1.0));

	~Camera();

	/* Getters */
	glm::mat4 GetProjectionMatrix() const { return m_projection; }
	glm::mat4 GetViewMatrix() const { return m_view; }

	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetLookAtTarget() { return m_lookAtTarget; }
	glm::vec3 GetUpVector() { return m_UpVector; }

	glm::mat4 GetMatrix();


	/* Setters */
	void SetFieldOfView( const unsigned int fov) { m_fieldOfView = fov%360; }
	void SetPixelDimensions(float width, float height) { m_pixelWidth = width; m_pixelHeight = height; }

	void SetPosition(glm::vec3 pos) { m_position = pos; }
	void SetLookAtTarget(glm::vec3 target) { m_lookAtTarget = target; }
	void SetUpVector(glm::vec3 up) { m_UpVector = up; }

private:

	float m_nearClipPlane;			// Distance to near clip plane
	float m_farClipPlane;			// Distance of far clip plane

	float m_pixelWidth;				// Camera Pixel Width
	float m_pixelHeight;			// Camera Pixel Height

	unsigned int m_fieldOfView;		// Field of view in Degrees

	glm::vec3 m_position;			// Camera Position
	glm::vec3 m_lookAtTarget;		// Camera LookAtTarget
	glm::vec3 m_UpVector;			// Camera UpVector


	glm::mat4 m_projection;			// Projection Matrix (perspective)
	glm::mat4 m_view;				// Camera View Matrix (position)

	// Uniforms
	GLuint m_viewUniform;
	GLuint m_projectionUniform;

};