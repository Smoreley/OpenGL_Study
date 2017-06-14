#include "stdafx.h"
#include "Camera.h"

Camera::Camera(unsigned int fov, vec3 pos, vec3 lookAtTarget) : m_fieldOfView(fov), m_position(pos), m_lookAtTarget(lookAtTarget), m_nearClipPlane(0.1f), m_farClipPlane(100.0f)
{
	m_pixelWidth = 1280;
	m_pixelHeight = 720;

	m_projection = glm::perspectiveFov(glm::radians((float)m_fieldOfView), m_pixelWidth, m_pixelHeight, m_nearClipPlane, m_farClipPlane);

	float r = 10.0f;
	mat4x4 view = glm::mat4(1.0f);
	view = glm::lookAt(
		vec3(r, 5.0f, r),
		vec3(0.0f),
		vec3(0.0, 1.0, 0.0));

	m_view = m_projection * view;
}

Camera::~Camera() {

}

mat4x4 Camera::GetMatrix() {
	// Combines projection and view matrixes together

	float r = 10.0f;
	mat4x4 view = mat4x4(1.0f);
	view = glm::lookAt(
		vec3(r, 5.0f, r),
		vec3(0.0f),
		vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(m_position, m_lookAtTarget, m_UpVector);
	m_view = m_projection * view;

	return m_view;
}

void Camera::CalcPerspective() {
	m_projection = glm::perspectiveFov(glm::radians((float)m_fieldOfView), m_pixelWidth, m_pixelHeight, m_nearClipPlane, m_farClipPlane);
}