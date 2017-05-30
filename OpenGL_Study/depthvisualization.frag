#version 430 core

out vec4 color;

in VS_OUT
{
	vec4 color;
} fs_in;

float near = 1.0; 
float far  = 10.0;   
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

float FallOff(float dist)
{
	// if a = 1 then no fall-off, instead it is constant
	// if b = 1 then linear fall-off
	// if c = 1 then quadratic fall-off
	float a = 0, b = 1, c = 0;

	float result = sqrt(1.0/(a + b * dist + c * pow(dist, 2)));
	return result;
}

void main(void)
{
	vec2 screen_res = vec2(1280, 720);
	vec2 st = gl_FragCoord.xy/screen_res;

	//float depth = LinearizeDepth(gl_FragCoord.z) / far;

	// Fall-off depth
	// float depth = FallOff(gl_FragCoord.w * 100.0);

	// Simple Depth
	// depth = 1.0 - (gl_FragCoord.z/gl_FragCoord.w) / 1.0;

	// Fog
	const float LOG2 = 1.442695;
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float density = 0.3;

	float fogFactor = exp2(-density * density * z * z * LOG2);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	vec3 fogColor = vec3(0.1, 0.1, 0.1);
	vec3 otherColor = vec3(0.0, gl_FragCoord.w/3.0, 1.0);

	color = vec4(mix(fogColor, otherColor, fogFactor), 1.0);

	//color = vec4(vec3(depth), 1.0f);
	//color = vec4(vec3(fs_in.color.x, fs_in.color.y, fs_in.color.z) * depth, 1.0f);

}