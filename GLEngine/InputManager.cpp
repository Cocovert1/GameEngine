#include "InputManager.h"

namespace GLEngine {

	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		//if not in map, creates it, else sets to true
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		//if not in map, creates it, else sets to true
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		//if there is key it = key, else it will = end aka. end of the hash since it didn't find it
		auto it = _keyMap.find(keyID);

		//if it points to a key, return it
		if (it != _keyMap.end()) {
			//second =  value in <key, value> hash
			return it->second;
		}
		else {
			return false;
		}
		
	}

}
