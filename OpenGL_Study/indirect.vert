#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (location = 10) in uint draw_id;

uniform mat4 u_mv_matrix;
uniform mat4 u_proj_matrix;
uniform float u_time;

out VS_out
{
	vec4 color;
	vec2 texcoord;
} vs_out;

void main(void) {
	
	gl_Position = u_proj_matrix * u_mv_matrix * vec4(position, 1.0);



}