#pragma once

typedef unsigned char uint8;

class ModelLoading : public Progbase
{
public:
	int start();
	int end();
	int render();
	int update(const double);

private:
	double deltaTime{ 0 };
	double time{ 0 };

	Model tempor_model;

	struct {
		GLint mv;
		GLint proj;
		GLint view;
		GLint time;
	} m_UniformLocation;

	std::string m_fileName;


	uint8 loadFile(const std::string &);

};


//struct ModelStructure {
//	glm::vec3 vert;
//	glm::vec3 uvs;
//	glm::vec3 normals;
//};