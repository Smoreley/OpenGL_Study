#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 colors;

layout(std140) uniform TransformBlock
{
	float scale;
	vec3 translation;
	float rotation[3];
	mat4 projection_matrix;
} transform;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform mat4 u_mv_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_proj_matrix;

void main(void)
{

	// Project * View * Model View * Position
	gl_Position = u_proj_matrix * u_view_matrix * u_mv_matrix * position;
	//gl_Position = u_proj_matrix * u_mv_matrix * position;

	//gl_Position = transform.porjection_matrix * position;

	vs_out.color = vec4(0.0);
}