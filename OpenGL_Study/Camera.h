#pragma once

class Camera
{
public:
	Camera(unsigned int fov = 60, vec3 pos = vec3(0.0), vec3 lookAtTarget = vec3(1.0));

	~Camera();

	/* Getters */
	mat4 GetProjectionMatrix() const { return m_projection; }
	mat4 GetViewMatrix() const { return m_view; }

	vec3 GetPosition() { return m_position; }
	vec3 GetLookAtTarget() { return m_lookAtTarget; }
	vec3 GetUpVector() { return m_UpVector; }

	mat4 GetMatrix();


	/* Setters */
	void SetFieldOfView( const unsigned int fov) { m_fieldOfView = fov%360; CalcPerspective(); }
	void SetPixelDimensions(float width, float height) { m_pixelWidth = width; m_pixelHeight = height; CalcPerspective(); }

	void SetPosition(vec3 pos) { m_position = pos; }
	void SetLookAtTarget(vec3 target) { m_lookAtTarget = target; }
	void SetUpVector(vec3 up) { m_UpVector = up; }

	void SetNearClipPlane(float near) { m_nearClipPlane = near; CalcPerspective(); }
	void SetFarClipPlane(float far) { m_farClipPlane = far; CalcPerspective(); }

private:

	float m_nearClipPlane;			// Distance to near clip plane
	float m_farClipPlane;			// Distance of far clip plane

	float m_pixelWidth;				// Camera Pixel Width
	float m_pixelHeight;			// Camera Pixel Height

	unsigned int m_fieldOfView;		// Field of view in Degrees

	vec3 m_position;			// Camera Position
	vec3 m_lookAtTarget;		// Camera LookAtTarget
	vec3 m_UpVector;			// Camera UpVector


	mat4 m_projection;			// Projection Matrix (perspective)
	mat4 m_view;				// Camera View Matrix (position)

	// Uniforms
	GLuint m_viewUniform;
	GLuint m_projectionUniform;


	void CalcPerspective();
};