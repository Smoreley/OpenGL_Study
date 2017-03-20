#version 430 core

layout(binding=0) uniform sampler2D samp_one;
layout(binding=1) uniform sampler2D samp_two;
uniform float time;

in VS_OUT
{
	vec4 color;
	vec2 texcoord;
} fs_in;

out vec4 color;

void main(void) 
{
	vec4 tex_one = texture(samp_one, fs_in.texcoord);
	vec4 tex_two = texture(samp_two, fs_in.texcoord);

	color = mix(tex_one, tex_two, (sin(time/1.5)+1.0)/2.0);
	
	// Wave
	if(fs_in.texcoord.y < 0.5) {
	color = mix(
		texture(samp_one,
			vec2(fs_in.texcoord.x+ sin(fs_in.texcoord.y * 60.0 + time * 4.0) / 30.0, 1.0 - fs_in.texcoord.y))
			* vec4(0.7, 0.7, 1.0, 1.0),
		color,
		(sin(time/1.5)+1.0)/2.0);
	}
}