#include "Texture.h"

ENGINE::Texture::Texture(const std::string path)
{
	// Load file and decode image.
	std::vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, path.c_str());

	// If there's an error, display it.
	if (error != 0)
	{
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		assert(false);
	}

	// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	size_t u2 = 1; while (u2 < width) u2 *= 2;
	size_t v2 = 1; while (v2 < height) v2 *= 2;

	// Make power of two version of the image.
	std::vector<unsigned char> image2(u2 * v2 * 4);
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			for (size_t c = 0; c < 4; c++)
			{
				image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
			}
		}
	}

	//Generate opengl needed things
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		u2,	//width
		v2,	//height
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		&image2[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ENGINE::Texture::_bind()
{
	glActiveTexture(numberOfTexture);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void ENGINE::Texture::_unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
