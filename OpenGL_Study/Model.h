#pragma once
#include <string>
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Mesh.h"

/* Model loading */
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

using namespace std;

class Model {
public:
	Model(GLchar* path) {
		this->LoadModel(path);
	}

	void Draw() {
		for (GLuint i = 0; i < m_meshes.size(); i++) {
			m_meshes[i].Draw();
		}
	}

private:
	vector<Mesh> m_meshes;
	string m_directory;

	// 
	void LoadModel(string path) {
		Assimp::Importer import;	// problem code

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

	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
		vector<Texture> vTex;

		return vTex;
	}
};