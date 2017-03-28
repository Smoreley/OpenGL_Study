#version 430 core

// Vertex position
layout (location = 0) in vec4 v_position;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

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
	
	//vec4 offset = vec4(float(gl_InstanceID >> 10) - 512.0, 0.0f, float(gl_InstanceID & 0x3FF) - 512.0, 0.0f);
	vec4 offset = vec4((gl_InstanceID/10.0) - 2.0, -3.0, random(4, gl_InstanceID)/15485863, 1);

	vec4 position = (v_position + offset);

	gl_Position = (proj_matrix * mv_matrix) * position;
}