#pragma once
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include <assimp\postprocess.h>

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh
{
public:
	/* Mesh Data */
	vector<Vertex> m_vertices;
	vector<GLuint> m_indices;
	vector<Texture> m_textures;

	// Constructor
	Mesh(vector<Vertex> vert, vector<GLuint> indices, vector<Texture> textures) {
		m_vertices = vert;
		m_indices = indices;
		m_textures = textures;
		this->SetupMesh();
	}

	// Render 
	void Draw() {
		// Bind appropriate Textures
		GLuint diffuseNr = 1;
		GLuint specular = 1;

		for (GLuint i = 0; i < m_textures.size(); i++) {
			glActiveTexture(GL_TEXTURE + i);		// Activate proper texture before binding

			// Set the sampler to the correct texture
			//glUniform1i((glGetUniformLocation(shader.program, (name + shader).c_str()), i);

			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
		}

		// Draw Mesh
		glBindVertexArray(VAO);

		if (m_wireframeMode) {
			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Good practice to set things back to default
		for (GLuint i = 0; i < m_textures.size(); i++) {
			glActiveTexture(GL_TEXTURE + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

	void setWireframe(bool wireframe) { m_wireframeMode = wireframe; }

private:
	/* Render Data */
	GLuint VAO, VBO, EBO;
	bool m_wireframeMode;

	void SetupMesh() {
		m_wireframeMode = false;

		// Create buffers & arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Data
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

		// Element Buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoords));

		glBindVertexArray(0);
	}

};