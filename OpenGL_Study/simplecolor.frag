#version 430 core

out vec4 color;

in VS_OUT
{
	vec4 color;
} fs_in;

void main(void)
{
	vec2 screen_res = vec2(1280, 720);
	vec2 st = gl_FragCoord.xy/screen_res;
	
	vec3 base_color = vec3(0.0);
	base_color = vec3(st.x, st.y, 0.0);

	st *= 32;
	st = fract(st);

	float radius = 0.9;
	vec2 pos = vec2(0.5)-st;

	float circle = smoothstep(1.0-radius, 1.0-radius+radius*0.2, 1.0-dot(pos, pos)*3.14);
	base_color -= vec3(1.0-circle);


	// If given color doesn't equal zero set it as the color
	if(fs_in.color.xyz != vec3(0.0)) {
		base_color = fs_in.color.xyz;
	}

	color = vec4(base_color, 1.0);
}