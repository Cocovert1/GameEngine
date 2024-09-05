#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Bengine {

	Sprite::Sprite() : _vboID(0) {

	}
	Sprite::~Sprite() {
		// delete the buffer, free up space
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}


	//Initializes the sprite VBO. X,Y,width and height are
	//in the normalized device coordinate space, [-1, 1]
	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		// generate the buffer if it hasn't already been generated
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID); //this fnc will create names for n new buffer objects and stores them in the VBO.
		}

		// this array holds vertex data
		// it has 6 vertices, each vertex has 2 floats for x and y
		Vertex vertexData[6];

		//first triangle of the square
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle of the square
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		// for loop to hardcode color values
		//for (int i = 0; i < 6; i++) {
		//	vertexData[i].setColor(255, 0, 255, 255);
		//}

		//experimental for learning, visualize interpollation (color spread around two points) You can stop interpolation in shader
		vertexData[4].setColor(0, 0, 255, 255);
		vertexData[4].setColor(0, 255, 0, 255);


		// Tell opengl to bind our vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //GL_STATIC_DRAW tells GL that were not modifying this data often, so it knows where to store it
		// since its static the GL might be inclined to store it in the VRAM.

		// unbind buffer (optional)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw() {
		//bind texture
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		// bind buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID); // we specify we want to bind an array buffer, and point to it.

		//Tell opengl we want to use the first attribute array. We only need one array right now since we are only using position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Point opengl to the data in our VBO
		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//This is the color attribute pointer
		// we set normalization to true since our shader input is in 0-255, which is not normalized
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//attrib pointer for UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


		// draws the points
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable after use
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}