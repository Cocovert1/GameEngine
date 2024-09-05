#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Bengine.h"

namespace Bengine {

	int init() {
		// initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// sets double buffers, same concept of having a onscreen buffer, and offscreen buffer
		// makes animation and movement smooth, no flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}