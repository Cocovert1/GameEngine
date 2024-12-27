#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

namespace GLEngine {

	// fnc to output error
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}
}