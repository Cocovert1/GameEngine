#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Bengine {

	TextureCache::TextureCache() {

	}
	TextureCache::~TextureCache() {

	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		// auto becomes the return type of this fnc
		auto mit = _textureMap.find(texturePath); //lookup the texture and see if its in the map
		//if the texture exists in cache, then mit will be pointing to it.

		//check not in map
		if (mit == _textureMap.end()) {
			//load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//map takes input key,value pair
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "New Texture Loaded \n";
			return newTexture;
		}

		/*
		*	mit is an iterator with a key and value pair.
		*	With iterator we use the -> operator to access them
		*	Since we are doing a path, texture pair, we want to access the second value.
		*/
		std::cout << "Cache Texture Loaded \n";
		return mit->second;

	}
}