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

void main(void)
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	color = vec4(vec3(depth), 1.0f);
}