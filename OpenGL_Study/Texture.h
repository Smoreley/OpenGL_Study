#pragma once
#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	GLuint Load(const char* filename);

	GLuint tex_name;

	int width;
	int height;

private:

};

Texture::Texture()
{
}

GLuint Texture::Load(const char* filename) {
	gli::texture tex = gli::load(filename);

	if (tex.empty()) return 0;

	gli::gl GL(gli::gl::PROFILE_GL33);

	gli::gl::format const tex_format = GL.translate(tex.format(), tex.swizzles());
	GLenum tex_target = GL.translate(tex.target());

	glGenTextures(1, &tex_name);
	glBindTexture(tex_target, tex_name);

	glm::tvec3<GLsizei> const tex_extent(tex.extent());

	glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(tex_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(tex_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(tex.levels() - 1));
	glTexParameteriv(tex_target, GL_TEXTURE_SWIZZLE_RGBA, &tex_format.Swizzles[0]);

	// Make room in storage
	glTexStorage2D(tex_target, static_cast<GLint>(tex.levels()), tex_format.Internal, tex_extent.x, tex_extent.y);

	GLint tex_level = 0;

	if (gli::is_compressed(tex.format())) {
		glCompressedTexSubImage2D(
			tex_target,
			tex_level,
			0,
			0,
			tex_extent.x,
			tex_extent.y,
			tex_format.Internal,
			tex.size(tex_level),
			tex.data(0, 0, tex_level)
		);
	}
	else {
		// TODO: Implement non-compressed texture loading
		std::cerr << "Texture loading for uncompressed textures not yet implemented" << std::endl;
		return 0;
	}

	return tex_name;
}

Texture::~Texture()
{
}
