#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 colors;
layout (location = 2) in vec2 coords;

out VS_OUT
{
	vec4 color;
	vec2 texcoord;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
	vs_out.texcoord = coords;

	gl_Position = proj_matrix * mv_matrix * position;
	//gl_Position = transform.porjection_matrix * position;

	vs_out.color = colors * vec4(1.0, 1.0, 1.0, 1.0);
}