#pragma once

class Model;
class Camera;

class ClipDistance : public Progbase {
public:
	int start();
	int end();
	int render();
	int update(const double);

private:
	double m_deltaTime;
	double m_time;

	GLuint m_vao;
	GLuint m_vbo;

	GLuint m_modelView_location;
	GLuint m_projection_location;
	GLuint m_view_location;

	GLuint m_clipPlane_location;

	Model* m_pModel;
	Camera* m_pCamera;

};