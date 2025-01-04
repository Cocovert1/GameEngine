#include "Camera2D.h"

namespace GLEngine {

	Camera2D::Camera2D() : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _scale(1.0f), _needsMatrixUpdate(true), _screenWidth(500), _screenHeight(500), _orthoMatrix(1.0f)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update() {

		if (_needsMatrixUpdate) {
			//camera translation (this moves)
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//camera scale (this resizes)
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}

	}
	glm::vec2 Camera2D::convertScreenCoordsToWorldCoords(glm::vec2 screenCoords)
	{ 
		/* for scalability and simplicity, we want to convert how we measure our coordinates.Up until now, the top left is 0, 0 and bottom right is the screen width,height
		This isn't ideal, we would much rather preffer if the center of the screen were 0,0 just like a normal x,y graph. Then the top left would be -sw/2 and -sh/2 and bottom
		right would be sw/2 and sh/2. */
		
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		screenCoords /= _scale;
		screenCoords += _position; //account for camera position
		
		return screenCoords;
	}
}