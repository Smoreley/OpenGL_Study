#version 430 core

layout (location = 0) in vec4 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
	gl_position = projection_matrix * view_matrix * model_matrix * position;

}
