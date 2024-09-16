#include "MainGame.h"
#include <Bengine/Errors.h>
#include <Bengine/ResourceManager.h>

#include <iostream>
#include <string>

MainGame::MainGame() : _screenWidth(1024), _screenHeight(768), _time(0.0f), _gameState(GameState::PLAY), _maxfps(60.0f){
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {}

void MainGame::run() {
	initSystems();

	//main game loop
	gameLoop();
}

// setup our window and opengl
void MainGame::initSystems() {

	Bengine::init();

	//create the window
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {

	while (_gameState != GameState::EXIT) {
		//used for frame time measuring for max fps
		float startTicks = SDL_GetTicks();

		processInput();
		//increment the uniform variable time
		_time += 0.01;

		_camera.update();

		drawGame();
		calculateFPS();

		//print every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;

		//FPS limit
		if (1000.0f / _maxfps > frameTicks) {
			SDL_Delay((1000.0f / _maxfps) - frameTicks); //our fps is lower than desired, we want to delay by  the missing ms
		}
	}
}
void MainGame::processInput() {
	// an SDL event object is any input, it can be a quit button, key up or down, etc...
	SDL_Event evnt;

	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

	// polling, systems requests every few ms if there is any input
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		//if quit event, stop game
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym) {
				case SDLK_w:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
					break;
				case SDLK_s:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
					break;
				case SDLK_a:
					_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
					break;
				case SDLK_d:
					_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
					break;
				case SDLK_q:
					_camera.setScale(_camera.getScale() + SCALE_SPEED);
					break;
				case SDLK_e:
					_camera.setScale(_camera.getScale() - SCALE_SPEED);
					break;
			}
			break;
		}
	}
}

void MainGame::drawGame() {
	// tell opengl what depth it needs to clear to
	glClearDepth(1.0);
	// clear our buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//enable attributes
	_colorProgram.use();
	
	//use the first texture
	glActiveTexture(GL_TEXTURE0);

	//for uniform, bind texture 0
	GLint textureLocation = _colorProgram.getUniformLocaiton("mySampler");
	glUniform1i(textureLocation, 0);

	//will fetch the location of our uniform variable time
	GLuint timeLocation = _colorProgram.getUniformLocaiton("time");
	glUniform1f(timeLocation, _time); //send the uniform to GPU, do before drawing

	//Set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocaiton("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	//upload matrix to GPU
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//disable attributes
	_colorProgram.unuse();

	//swap buffer so that there is no flickering
	_window.swapBuffer();

}

void MainGame::calculateFPS() {
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
	} else {
		_fps = 60.0f;
	}
}

