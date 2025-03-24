#pragma once
#include <string>
#include <GL/glew.h>

class Texture {
public:
	int width, height, channels;

	Texture(const std::string& path, GLenum type = GL_TEXTURE_2D);
	~Texture();

	void bind_texture(unsigned int slot) const;

	GLuint getID();

private:
	GLuint ID;
	GLenum tex_type;
	
};