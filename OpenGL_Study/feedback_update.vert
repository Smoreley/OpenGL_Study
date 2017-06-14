#version 430 core

layout (location = 0) in vec4 position_mass;	// position and mass (mass is the w component)
layout (location = 1) in vec3 velocity;			// current velocity of the vertex
layout (location = 2) in ivec4 connection;		// Connection Vector

uniform samplerBuffer tex_position;

// Outputs
out VS_OUT
{
	vec4 tf_position_mass;
	vec3 tf_velocity;
} vs_out;

const vec3 grav = vec3(0.00, -0.08, 0.0);	// Gravity

uniform float t = 0.03;						// Timestep
uniform float k = 5.1;						// Spring constant
uniform float c = 4.0;						// Damping constant
uniform float rest_length = 0.88;			// Spring resting length

void main(void)
{
	vec3 p = position_mass.xyz;		// p is the position of our vertex
	float m = position_mass.w;		// m is the mass part of our vertex
	vec3 u = velocity;				// u is our Initial Velocity
	vec3 f = grav * m -c * u;	// f is the force on the mass
	bool fixed_node = true;

	for (int i = 0; i < 4; i++) {
		if (connection[i] != -1) {
			vec3 q = texelFetch(tex_position, connection[i]).xyz;
			vec3 d = q - p;
			float x = length(d);
			f += -k * (rest_length -x) * normalize(d);
			fixed_node = false;
		}
	}

	if (fixed_node) { f = vec3(0.0); }

	vec3 a = f / m;							// Acceleration due to force
	vec3 s = u * t + 0.5 * a * t * t;		// Displacement
	vec3 v = u + a * t;						// Final velocity

	s = clamp(s, vec3(-25.0), vec3(25.0));		// Constrain the absolute value of the displacement per step

	// Write the outputs
	vs_out.tf_position_mass = vec4(p + s, m);
	vs_out.tf_velocity = v;
}