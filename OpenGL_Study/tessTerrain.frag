#version 430 core

out vec4 color;

layout (binding = 1) uniform sampler2D tex_color;

in TES_OUT
{
	vec2 tc;
	vec3 world_coord;
	vec3 eye_coord;
} fs_in;

void main(void)
{
	//color = vec4(0.0,fs_in.eye_coord.y/10.0f, 0.0, 1.0);

	color = texture(tex_color, fs_in.tc);
}