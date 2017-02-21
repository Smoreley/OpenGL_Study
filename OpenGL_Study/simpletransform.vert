#version 430 core

layout (location = 0) in vec4 position;

in vec4 colors;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform mat4 mv_matrix;

void main(void)
{
	gl_Position = mv_matrix * position;
	vs_out.color = position + vec4(0.5, 0.5, 0.0, 1.0);
}