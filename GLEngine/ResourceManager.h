#pragma once
#include "TextureCache.h"
#include <string>

namespace GLEngine {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}