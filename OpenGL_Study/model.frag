#version 430 core

out vec4 color;

in VS_OUT
{
	vec2 texCoords;
} fs_in;

void main(void)
{
	color = vec4(fs_in.texCoords.x, fs_in.texCoords.y, 1.0, 1.0);

}