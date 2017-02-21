#version 430 core

out vec4 color;

in VS_OUT
{
	vec4 color;
} fs_in;

void main(void)
{
	color = fs_in.color * gl_FragCoord / vec4( 1280, 720, 1,1);
}