#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


out VS_OUT
{
	vec2 texCoords;
	vec4 color;
	vec3 normal;
	vec3 light;
} vs_out;

// Uniforms
uniform mat4 u_mv_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_proj_matrix;

// uniform float u_time;

uniform vec4 u_clip_plane = vec4(0.0, 1.0, 0.0, 1.0);

void main(void)
{
	vec4 p = u_mv_matrix * position;

	// Simple Lighting
	vs_out.normal = mat3(u_mv_matrix) * normal;
	vs_out.light = vec3(0.0, 500.0, 0.0) - p.xyz;

	// Clipping
	gl_ClipDistance[0] = dot(position, u_clip_plane);

	gl_Position = u_view_matrix * p;
	vs_out.texCoords = texCoords;
	vs_out.color.w = dot(normalize(position), u_clip_plane) + 0.25;

}