#pragma once
#include "stdafx.h"

class Object
{
public:
	Object();
	~Object();

	inline void render(unsigned int instance_count = 1, unsigned int base_instance = 0) {
		render_sub_object(0, instance_count, base_instance);
	}

	void render_sub_object(unsigned int object_index, unsigned int instance_count = 1, unsigned int base_instance = 0);

	void get_sub_object(unsigned int index, GLuint &first, GLuint &count) {
		if (index >= num_sub_objects) {
			first = 0;
			count = 0;			
		}
		else {
			first = sub_object[index].first;
			count = sub_object[index].count;
		}
	}

	unsigned int const get_sub_object_count() { return num_sub_objects; };
	GLuint const get_vao() { return vao; };
	void load(const char *filename);
	void free();

private:
	GLuint data_buffer;
	GLuint vao;
	GLuint index_type;
	GLuint index_offset;

	static const unsigned int MAX_SUB_OBJECTS = 256;
	
	unsigned int num_sub_objects;

	typedef struct SubObjectDeclaration {
		unsigned int first;
		unsigned int count;
	};

	SubObjectDeclaration sub_object[MAX_SUB_OBJECTS];
};
