#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Bengine {

	/*
		The bitwise OR works on the bit level
		Say you have 1010 and 1011, using bitwise we would get 1011
		Bitwise will apply the logic to the individual pairs of bits
		This enables us to basically distinguish flags in the bits
	*/

	//setup hexadecimal enum since we want the user to be able to use multiple flags together, so a bitwise OR would be best
	//since it would allow us to distinguish flags using just one paramater/flag
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};

}
