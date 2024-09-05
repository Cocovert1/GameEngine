#pragma once

#include <GL/glew.h>

namespace Bengine {

	struct Position {
		float x;
		float y;
	};

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		float u;
		float v;
	};

	struct Vertex {
		//these two should make up 11 bytes, we ideally want it to be a multiple of 4 for alignment issues
		//float position[2]; //8 bytes
		//GLubyte color[4]; //4 bytes (red,green,blue,alpha) we add alpha to make it 4 bytes so total is 12

		//we change it to struct so that we don't have to call stuff position[0] and position[1], instead we do position.x or position.y
		Position position;

		//same for color
		Color color;

		//make UV texture coordinates
		UV uv;


		//functions do not increate the size of a struct in bytes
		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

	};

}