#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bengine {

	// we handle our 2d camera in a matrix view
	class Camera2D
	{
	public:

		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		//setter and getter
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		glm::vec2 getPosition() { return _position; }

		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }
		float getScale() { return _scale; }

		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth, _screenHeight;
		float _scale;
		bool _needsMatrixUpdate;
		glm::vec2 _position; //2 floats
		glm::mat4 _cameraMatrix; //orthographic matrix
		glm::mat4 _orthoMatrix;
	};

	/*
	Explanation of how the camera works: In OpenGL, frames are rendered from left to right and top to bottom.
	In a 2D game, to create the effect of movement, we have to move the frames. If we want to look left, we move the pixels right.
	
	So how do we represent this for the GPU to render? We use a orthoMatrix. Any movement we make, we need to input it in the matrix,
	using matrix mathematics, we can determine what the movement will need to be for the pixels. So when an input to move is made,
	first a translation of the matrix will occur, then it will be resized to scale.
	*/

}
