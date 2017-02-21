#version 430 core

in vec4 position;
in vec4 colors;

out VS_OUT
{
	vec4 color;
} vs_out;

void main(void)
{
	gl_Position = position;
	vs_out.color = position + vec4(0.5, 0.5, 0.5, 1.0);
}