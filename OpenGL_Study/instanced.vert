#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 instance_color;
layout (location = 2) in vec4 instance_position;

out VS_OUT
{
	vec4 color;
} vs_out;

void main(void)
{
	gl_Position = position + instance_position;

	vs_out.color = instance_color;
}