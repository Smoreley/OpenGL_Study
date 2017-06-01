#pragma once
//#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#include <iostream>

class BulletDebugRender : public btIDebugDraw {
public:
	//BulletDebugRender(void) {}
	//virtual ~BulletDebugRender(void) {}

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

	virtual void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {}
	virtual void reportErrorWarning(const char* warningString) { std::cout << "Thar be an error in the debug-render for bullet" << std::endl; }
	virtual void draw3dText(const btVector3 &location, const char* textString) {}

	virtual void setDebugMode(int debugMode) { m_debugMode = (DebugDrawModes)debugMode; };
	virtual int getDebugMode() const { return m_debugMode; }

	void Test_init() {

		line_program = Helper::compileShaders("line.vert", "simplecolor.frag");

		glGenVertexArrays(1, &temp_vao);
		glGenBuffers(1, &temp_vbo);

		const GLfloat line_vp[] = {
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
		};

		glBindVertexArray(temp_vao);
		glBindBuffer(GL_ARRAY_BUFFER, temp_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(line_vp), &line_vp, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

	}

	void Test_rend() {
		
		glUseProgram(line_program);
		glBindVertexArray(temp_vao);
		glDrawArrays(GL_LINE_LOOP, 0, 2);
		glBindVertexArray(0);			// Set vertex array to null

	}

private:
	DebugDrawModes m_debugMode;
	GLuint temp_vao, temp_vbo;
	GLuint line_program;
};