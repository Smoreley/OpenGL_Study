#pragma once
#include <LinearMath/btIDebugDraw.h>


class BulletDebugRender : public btIDebugDraw {
public:
	BulletDebugRender(void);
	~BulletDebugRender(void);

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

	virtual void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {}
	virtual void reportErrorWarning(const char* warningString) { std::cout << "Thar be an error in the debug-render for bullet" << std::endl; }
	virtual void draw3dText(const btVector3 &location, const char* textString) {}

	virtual void setDebugMode(int debugMode) { m_debugMode = (DebugDrawModes)debugMode; };
	virtual int getDebugMode() const { return m_debugMode; }

	void RenderMe();

	void SetCamera(Camera* cam) { m_camera = cam; }

private:
	DebugDrawModes m_debugMode;
	GLuint line_program;
	GLuint temp_vao, temp_vbo;

	// Uniforms
	GLuint m_modelViewLocation;
	GLuint m_projectionLocation;
	GLuint m_viewLocation;

	std::vector<GLfloat> myLines;
	GLfloat* tempArray;

	Camera* m_camera;
};