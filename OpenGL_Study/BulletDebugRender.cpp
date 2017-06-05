#include "stdafx.h"
#include "Helper.h"
#include "Camera.h"

#include <iostream>

#include <vector>

#include "BulletDebugRender.h"

BulletDebugRender::BulletDebugRender() {

	line_program = Helper::compileShaders("line.vert", "simplecolor.frag");

	// Generate opengl things
	glGenVertexArrays(1, &temp_vao);
	glGenBuffers(1, &temp_vbo);

	/* Uniforms */
	//m_modelViewLocation = glGetUniformLocation(line_program, "u_mv_matrix");
	m_projectionLocation = glGetUniformLocation(line_program, "u_proj_matrix");
	m_viewLocation = glGetUniformLocation(line_program, "u_view_matrix");


	tempArray = new GLfloat[6]{ 0,0,0, 1,1,1 };

}

BulletDebugRender::~BulletDebugRender() {

	// Cleanup OpenGL
	glDeleteBuffers(1, &temp_vbo);
	glDeleteVertexArrays(1, &temp_vao);

}


void BulletDebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	drawLine(from, to, color, color);
}

void BulletDebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	//SColorf fromC;  fromC.set(fromColor[0], fromColor[1], fromColor[2], fromColor[3]);
	//SColorf toC;    toC.set(toColor[0], toColor[1], toColor[2], toColor[3]);

	//Graphics->drawLine(from, to, fromC, toC);

	GLfloat line_vp[] = {
		from.x(), from.y(), from.z(),
		to.x(), to.y(), to.z()
	};

	myLines.push_back(from.x());
	myLines.push_back(from.y());
	myLines.push_back(from.z());

	myLines.push_back(to.x());
	myLines.push_back(to.y());
	myLines.push_back(to.z());

	glUseProgram(line_program);
}

void BulletDebugRender::RenderMe() {

	delete[] tempArray;
	tempArray = new GLfloat[myLines.size()];
	for (int i = 0; i < myLines.size(); i++) {
		tempArray[i] = myLines[i];
	}

	GLfloat* vp = tempArray;

	glBindVertexArray(temp_vao);
	glBindBuffer(GL_ARRAY_BUFFER, temp_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * myLines.size(), vp, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//glm::mat4 proj = glm::perspectiveFov(glm::degrees(60.0f), 1280.0f, 720.0f, 1.0f, 100.0f);
	//glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(proj));

	//float r = 10.0f;
	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::lookAt(
	//	glm::vec3(r, 5.0f, r),
	//	glm::vec3(0.0f),
	//	glm::vec3(0.0, 1.0, 0.0));
	//glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_camera->GetMatrix()));

	glUseProgram(line_program);
	glBindVertexArray(temp_vao);
	glDrawArrays(GL_LINES, 0, myLines.size()/3);
	glBindVertexArray(0);			// Set vertex array to null

	myLines.clear();
}