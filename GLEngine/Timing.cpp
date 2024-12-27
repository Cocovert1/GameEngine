#include "Timing.h"

#include <SDL/SDL.h>

namespace GLEngine {
	GLEngine::FpsLimiter::FpsLimiter() {}
	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}
	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		_maxfps = maxFPS;
	}
	void FpsLimiter::begin()
	{
		//used for frame time measuring for max fps
		_startTicks = SDL_GetTicks();
	}
	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//FPS limit
		if (1000.0f / _maxfps > frameTicks) {
			SDL_Delay((1000.0f / _maxfps) - frameTicks); //our fps is lower than desired, we want to delay by  the missing ms
		}
		return _fps;
	}
	void FpsLimiter::calculateFPS()
	{
			/*
				To calculate our fps, we want to get the ticks for each frame. The result will be ms/frame
				We convert it to frame/s, but that not enough. The f/s of each frame can vary drastically and
				it can be too sporadic. So we want to average out a number of frames and output that.
			*/

			//nbr of frames we average
			static const int NUM_SAMPLES = 10;
			static float frameTimes[NUM_SAMPLES]; //can only create a static array with a const value for its size
			static int currentFrame = 0;

			//this is start time and end time
			static float prevTicks = SDL_GetTicks();
			float currentTicks;
			currentTicks = SDL_GetTicks();

			_frameTime = currentTicks - prevTicks;
			frameTimes[currentFrame % NUM_SAMPLES] = _frameTime; //we are treating the array like a circular array/circular buffer

			//update end time to be new start time
			prevTicks = currentTicks;

			//move onto next frame
			currentFrame++;

			//we cannot do the average only dividing by NUM_SAMPLES as the first few frames don't count to 10
			//here we check if it is full using count
			int count;
			if (currentFrame < NUM_SAMPLES) {
				count = currentFrame;
			}
			else {
				count = NUM_SAMPLES;
			}

			//we divide by count here since we want the average of the number of frames in the array
			float frameTimeAverage = 0;
			for (int i = 0; i < count; i++) {
				frameTimeAverage += frameTimes[i];
			}
			frameTimeAverage /= count;

			//set the fps
			if (frameTimeAverage > 0) {
				_fps = 1000.0f / frameTimeAverage;
			}
			else {
				_fps = 60.0f;
			}
		}
}