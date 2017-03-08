#version 430 core

uniform sampler2D s;

in VS_OUT
{
	vec4 color;
} fs_in;

out vec4 color;

void main(void) 
{
	//color = texelFetch(s, ivec2(gl_FragCoord.xy), 0);
	//color = texture(s, gl_FragCoord.xy / textureSize(s, 0)) * fs_in.color;
	color = texture(s, gl_FragCoord.xy / textureSize(s, 0));
}