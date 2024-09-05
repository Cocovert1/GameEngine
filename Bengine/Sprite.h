#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

#include <string>

namespace Bengine {

	// A 2d quad that can be rendered to screen
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();

	private:
		int _x;
		int _y;
		int _width;
		int _height;
		/*
			vertex buffer ID
			vbo enables non-immediate mode rendering
			vb, vertex buffer, is a block of memory created and managed by opengl which acts as a buffer
		*/
		GLuint _vboID;
		GLTexture _texture;
	};

}