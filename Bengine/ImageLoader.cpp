#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace Bengine {

	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {}; //sets all values to 0

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		//want to populate our in with the buffer
		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("Failed to load PNG to buffer");
		}

		//run the decodePNG fnc
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0) {
			fatalError("Decode PNG failed to run. Error: " + std::to_string(errorCode));
		}

		//generate opengl texture object
		glGenTextures(1, &(texture.id));

		//bind texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//upload image data to texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		//give parameters to texture (i don't understand these)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//what is mipmap'ing, its taking a picture and make it smaller on the screen. There is no reason to load all the details of a big picture if the pic is small
		//a linear mipmap min filter means that it will mipmap the pixels in a linear fashion as it gets smaller. 
		//so mipmap will average out the pixels of a texture as it gets smaller

		glGenerateMipmap(GL_TEXTURE_2D);

		//unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//fill in the h and w of the picture
		texture.width = width;
		texture.height = height;

		return texture;
	}

}