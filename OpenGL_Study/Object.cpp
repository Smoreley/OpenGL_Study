#include "Object.h"

// Constructor
Object::Object() : data_buffer(0), index_type(0), vao(0) {}

// Deconstruction
Object::~Object() {}

void Object::load(const char *filename) {
	FILE *infile;
	fopen_s(&infile, filename, "rb");

	size_t filesize;
	char *data;

	this->free();

	fseek(infile, 0, SEEK_END);
	filesize = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	data = new char[filesize];

	fread(data, filesize, 1, infile);

	char *ptr = data;
	



	// Cleanup
	delete[] data;
	fclose(infile);

}

void Object::free() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &data_buffer);

	vao = 0;
	data_buffer = 0;
}

void Object::render_sub_object(unsigned int object_index, unsigned int instance_count, unsigned int base_instance) {
	glBindVertexArray(vao);

	if (index_type != GL_NONE) {
		glDrawElementsInstancedBaseInstance(GL_TRIANGLES,
			sub_object[object_index].count,
			index_type,
			(void*)sub_object[object_index].first,
			instance_count,
			base_instance
		);
	}
	else {
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES,
			sub_object[object_index].first,
			sub_object[object_index].count,
			instance_count,
			base_instance
		);
	}

}
