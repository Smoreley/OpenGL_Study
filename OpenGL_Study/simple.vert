#version 430 core

in vec4 position;
layout (location = 2) in vec2 coords;

out VS_OUT
{
	vec4 color;
	vec2 texcoord;
} vs_out;

void main(void)
{
	vs_out.texcoord = coords;
	gl_Position = position;
	vs_out.color = position + vec4(0.5, 0.5, 0.5, 1.0);
}