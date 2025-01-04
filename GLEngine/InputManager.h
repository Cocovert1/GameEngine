#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace GLEngine {


	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);
		glm::vec2 getMouseCoords() const { return _mouseCoords; }

		bool isKeyPressed(unsigned int keyID);

	private:
		//hash map, will use more memory but will be faster (O(n) instead of log)
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;

	};

}

