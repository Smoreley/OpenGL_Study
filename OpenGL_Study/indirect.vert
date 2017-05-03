#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;

layout (location = 10) in uint draw_id;

uniform mat4 u_mv_matrix;
uniform mat4 u_proj_matrix;
uniform float u_time;

out VS_OUT
{
	vec4 color;
	vec2 texcoord;
} vs_out;

void main(void) {
	vs_out.texcoord = vec2(0.0);
	vs_out.color = vec4(1.0);
	
	vec4 pos = vec4(position, 1.0);	
	
	pos.x += draw_id * 0.1;
	pos.z += draw_id * 0.5;
	pos.y += (draw_id%10)*sin(draw_id) * 0.5f +
		( draw_id*sin(draw_id+u_time) * 0.5 )/20;

	vs_out.color = vec4(vec3(((draw_id)%10)/9.0f, 1.0, abs(sin(u_time))), 1.0);

	// Rotation
	mat4 m;
	float t = u_time * 0.1;
	float f = float(draw_id) / 25.0;

	float st = sin(t * 0.5 + f * 5.0);
    float ct = cos(t * 0.5 + f * 5.0);
    float j = fract(f);
    float d = cos(j * 3.14159);

    // Rotate around Y
    m[0] = vec4(ct, 0.0, st, 0.0);
    m[1] = vec4(0.0, 1.0, 0.0, 0.0);
    m[2] = vec4(-st, 0.0, ct, 0.0);
    m[3] = vec4(0.0, 0.0, 0.0, 1.0);


	// Set
	gl_Position = u_proj_matrix * u_mv_matrix * m * pos;
}