#version 430 core

out vec4 color;

in VS_OUT
{
	vec2 texCoords;
	vec4 color;
	vec3 normal;
	vec3 light;
} fs_in;

void main(void)
{
	vec3 N = normalize(fs_in.normal);
	vec3 L = normalize(fs_in.light);

	vec3 diffuse_albedo = vec3(0.8, 0.5, 0.3);

	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
	
	//color = vec4(fs_in.texCoords.x, fs_in.texCoords.y, 0.0, fs_in.color.w);
	color = vec4(diffuse, fs_in.color.w);
}