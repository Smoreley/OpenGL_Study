#version 430  core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 u_mv_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_proj_matrix;

out VS_OUT
{
	vec2 texCoords;
} vs_out;

void main(void)
{
	gl_Position = u_proj_matrix * u_view_matrix * u_mv_matrix * vec4(position, 1.0f);
	vs_out.texCoords = texCoords;
}