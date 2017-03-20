#version 430 core

uniform sampler2D samp;

in VS_OUT
{
	vec4 color;
	vec2 texcoord;
} fs_in;

out vec4 color;

void main(void) 
{
	//color = texelFetch(samp, ivec2(gl_FragCoord.xy), 0);

	//vec2 ts = textureSize(samp,0);
	//color = texture(samp, (gl_FragCoord.xy - vec2(ts.x/8.0, 0.0)) / ts);

	color = texture(samp, clamp(fs_in.texcoord.xy, 0.0, 1.0)) + fs_in.color;
}