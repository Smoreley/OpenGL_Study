#version 430 core

layout (location = 0) in vec3 position;

out VS_OUT
{
	vec4 color;
} vs_out;

void main(void)
{
	gl_Position = vec4((position) * 0.1, 1.0);
}