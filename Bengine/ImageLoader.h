#pragma once
#include "GLTexture.h"
#include <string>

namespace Bengine {

	//loads the texture
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}
