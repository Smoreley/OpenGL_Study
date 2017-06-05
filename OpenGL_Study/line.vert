#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec4 color;

out VS_OUT
{
	vec4 color;
} vs_out;


//uniform mat4 u_mv_matrix;		// Models position
uniform mat4 u_view_matrix;		// Put into view from the cameras point (cameras point of view)
uniform mat4 u_proj_matrix;		// Projection into screen space (perspective)

void main(void)
{
	//gl_Position = u_proj_matrix * u_view_matrix * vec4(position, 1.0);
	gl_Position = u_view_matrix * vec4(position, 1.0);

	vs_out.color = vec4(1.0);
}