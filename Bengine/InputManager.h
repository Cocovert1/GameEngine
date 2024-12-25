#pragma once

#include <unordered_map>

namespace Bengine {


	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

	private:
		//hash map, will use more memory but will be faster (O(n) instead of log)
		std::unordered_map<unsigned int, bool> _keyMap;

	};

}

