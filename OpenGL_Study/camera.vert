#version 430 core

layout (location = 0) in vec4 position;

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

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * position * 2;
	//gl_Position = transform.porjection_matrix * position;

	vs_out.color = vec4(1.0, 0.75, 0.5, 1.0);
}