#include "MainGame.h"
#include <Bengine/Errors.h>
#include <Bengine/ResourceManager.h>

#include <iostream>
#include <string>

#include <unordered_map>
#include <functional>

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
	_fpsLimiter.init(_maxfps);
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
		_fpsLimiter.begin();

		processInput();
		//increment the uniform variable time
		_time += 0.01;

		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();

		//print every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::processInput() {
	// an SDL event object is any input, it can be a quit button, key up or down, etc...
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
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
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}
	}

	//logically easier to follow, a pair of key and its function
	std::unordered_map<SDL_Keycode, std::function<void()>> keyActions = {
		{SDLK_w, [&]() { _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED)); }},
		{SDLK_s, [&]() { _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED)); }},
		{SDLK_a, [&]() { _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f)); }},
		{SDLK_d, [&]() { _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f)); }},
		{SDLK_q, [&]() { _camera.setScale(_camera.getScale() + SCALE_SPEED); }},
		{SDLK_e, [&]() { _camera.setScale(_camera.getScale() - SCALE_SPEED); }},
	};

	//iterate the hash map until the end, if key match, run its value function
	for (auto it = keyActions.begin(); it != keyActions.end(); ++it) {
		if (_inputManager.isKeyPressed(it->first)) {
			it->second(); 
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




