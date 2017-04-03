#version 430 core

// Vertex position
layout (location = 0) in vec4 v_position;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform float u_time;

layout (binding = 0) uniform sampler2D length_tex;

#define PI 3.14159265359

int random(int seed, int iterations) {
	int value = seed;
	int n;
	for(n = 0; n < iterations; n++) {
		value = ((value >> 7) ^ (value << 9)) * 15485863;
	}

	return value;
}

void main(void)
{
	vs_out.color = vec4(0.1, 0.3, 0.1, 0.0);

	// Texture
	int texsize = 256;
	vec4 offset = vec4( 
		((gl_InstanceID % texsize) - texsize/2.0f) + sin(gl_InstanceID),
		0.0f,
		(floor(gl_InstanceID / texsize) -texsize/2.0f) + 3.0f *fract(gl_InstanceID * .48f), 
		0.0f);
	vec2 texcoord = vec2( float(gl_InstanceID % texsize)/texsize, float(floor(gl_InstanceID / texsize))/texsize);

	// Rotation
	float angle = (gl_InstanceID * PI) + sin(gl_InstanceID) * gl_InstanceID*0.2f;
	float st = sin(angle);
	float ct = cos(angle);

	// Rotation around the y-axis
	mat4 rot;
	rot[0] = vec4(ct, 0.0, st, 0.0);
	rot[1] = vec4(0.0, 1.0, 0.0, 0.0);
	rot[2] = vec4(-st, 0.0, ct, 0.0);
	rot[3] = vec4(0.0, 0.0, 0.0, 1.0);

	vec3 wind_direction = vec3(0.0, 0.0, 1.0);


	vec4 position = (rot * v_position) + offset;

	position *= vec4(1.0, texture(length_tex, texcoord).b * 0.9 + 0.3, 1.0, 1.0);

	// Grass Growing using time
	position *= vec4(1.0, (sin(u_time * 5.0f)+1.2), 1.0, 1.0);

	gl_Position = (proj_matrix * mv_matrix) * position;
}