#version 430 core

layout(std140) uniform TransformBlock
{
	float scale;
	vec3 translation;
	float rotation[3];
	mat4 projection_matrix;
} transform;


void main(void)
{

}