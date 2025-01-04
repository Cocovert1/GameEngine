#include "Window.h"
#include "Errors.h"

namespace GLEngine {

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

		//enable alpha blending
		glEnable(GL_BLEND);

		/*Img has an alpha value (opacity). GL_SRC_ALPHA will take the alpha value of each pixel in the img. So if it is a blank pixel it will be 0, else it will be 1
		because we are drawing something on top. ONE_MINUS_SRC_ALPHA basically does the 1-img alpha. So whenever we have a pixel that we need to draw it will be 1-1 and
		when we don't want to draw anything (no background img)s 1-0. */
		
		//GL is trying to figure out if we wanna draw the sprite or if we want to draw the backgroudn img, in our case the blue background. So its asking us to do this math logic
		//so that it can determine how much of the "blue background" it will draw. Since we are using this simple 2D sprite, the alpha values are either 1 or 0.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer() {
		// swaps between draw and load buffers
		SDL_GL_SwapWindow(_sdlWindow);
	}

}