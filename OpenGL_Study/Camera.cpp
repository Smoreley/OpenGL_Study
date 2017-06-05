#include "stdafx.h"

#include "Camera.h"

Camera::Camera(unsigned int fov, glm::vec3 pos, glm::vec3 lookAtTarget) : m_fieldOfView(fov), m_position(pos), m_lookAtTarget(lookAtTarget), m_nearClipPlane(0.1f), m_farClipPlane(100.0f)
{
	m_pixelWidth = 1280;
	m_pixelHeight = 720;

	m_projection = glm::perspectiveFov(glm::radians((float)m_fieldOfView), m_pixelWidth, m_pixelHeight, m_nearClipPlane, m_farClipPlane);

	float r = 10.0f;
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(
		glm::vec3(r, 5.0f, r),
		glm::vec3(0.0f),
		glm::vec3(0.0, 1.0, 0.0));


	m_view = m_projection * view;
}


Camera::~Camera() {

}

glm::mat4 Camera::GetMatrix() {
	// Combines projection and view matrixes together

	float r = 10.0f;
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(
		glm::vec3(r, 5.0f, r),
		glm::vec3(0.0f),
		glm::vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(m_position, m_lookAtTarget, m_UpVector);

	m_view = m_projection * view;

	return m_view;
}