#pragma once

namespace GLEngine {

	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();
		
		//returns fps
		float end();

	private:
		void calculateFPS();

		float _fps;
		float _frameTime;
		float _maxfps;
		unsigned int _startTicks;
	};
}
