#include "Window.h"
#include "Errors.h"

namespace Bengine {

	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		//bitwise AND
		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		else if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		else if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		// create the window in SDL (title, where it will be centered on the screen, how big the screen is, flag)
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr) {
			fatalError("SDL Window could not be created");
		}

		// setup context of opengl (vertex, indices, etc...)
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created");
		}

		// setup glew
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("glewInit failed to run");
		}

		//Print OpenGL version
		std::printf("***    OpenGL Version: %s    ***\n", glGetString(GL_VERSION));

		// sets background color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0);

		// sets VSYNC on/off
		SDL_GL_SetSwapInterval(0);

		return 0;
	}

	void Window::swapBuffer() {
		// swaps between draw and load buffers
		SDL_GL_SwapWindow(_sdlWindow);
	}

}