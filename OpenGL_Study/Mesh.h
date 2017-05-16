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

	vector<Vertex> m_vertices;
	vector<GLuint> m_indices;
	vector<Texture> m_textures;

	Mesh(vector<Vertex> vert, vector<GLuint> indices, vector<Texture> textures) {

		m_vertices = vert;
		m_indices = indices;
		m_textures = textures;
		
		this->SetupMesh();
	}

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
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Good practice to set things back to default
		for (GLuint i = 0; i < m_textures.size(); i++) {
			glActiveTexture(GL_TEXTURE + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

private:
	/* Render Data */
	GLuint VAO, VBO, EBO;
	

	void SetupMesh() {
		// Create buffers & arrays
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		// Bind
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Data
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);


		// 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);


		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoords));

		glBindVertexArray(0);
	}

};

#include <assimp\Importer.hpp>
#include <assimp\scene.h>

class Model {
public:
	Model(GLchar* path) {
		
	}

	void Draw() {
		for (GLuint i = 0; i < m_meshes.size(); i++) {
			m_meshes[i].Draw();
		}
	};

private:
	vector<Mesh> m_meshes;
	string m_directory;

	// 
	void LoadModel(string path) {
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}

		m_directory = path.substr(0, path.find_last_of('/'));
		ProccessNode(scene->mRootNode, scene);
	}

	void ProccessNode(aiNode* node, const aiScene* scene) {
		// Process all the nodes meshes (if any)
		for (GLuint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(ProccessMesh(mesh, scene));
		}

		// Then do the same for each of the children
		for (GLuint i = 0; i < node->mNumChildren; i++) {
			ProccessNode(node->mChildren[i], scene);
		}
	}

	Mesh ProccessMesh(aiMesh* mesh, const aiScene* scene) {
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> textures;
		
		// Walk through each of the mesh vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;

			glm::vec3 vector;
			// Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			// Normal
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0]) {
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texcoords = vec;
			}
			else {
				vertex.texcoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}	// End of for-loop

		// faces
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		// Proccess Materials
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];


		}

		return Mesh(vertices, indices, textures);
	}

	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};