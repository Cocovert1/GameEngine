#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <GLEngine/Sprite.h>
#include <GLEngine/GLSLProgram.h>
#include <GLEngine/GLTexture.h>
#include <GLEngine/Window.h>
#include <GLEngine/GLEngine.h>
#include <GLEngine/Camera2D.h>
#include <GLEngine/InputManager.h>
#include <GLEngine/Timing.h>

#include <GLEngine/SpriteBatch.h>

#include <vector>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	GLEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	/*	Usually, each time we want to load a texture for a sprite, we would manually load that texture, which can lead
	*	to multiple instance of the texture being loaded.
	*
	*	Texture Cacheing, we want to store textures for use later on. If a sprite needs to use a texture, it will try to find it in cache.
	* 	Texture Cacheing enables us to optimize texture loading, since if it was already loaded, we stored it and can access it.
	*
	*	An array is not the most optimal data structure for texture cacheing, since it would run on O(n).
	*	A Binary Search Tree is a much better data structure for our purposes, since it's lookup time would be O(log n)
	*	in C++ this is known as a map	*/
	//std::vector <GLEngine::Sprite*> _sprites; //Deprecated

	GLEngine::GLSLProgram _colorProgram;
	GLEngine::Camera2D _camera;

	GLEngine::SpriteBatch _spriteBatch;

	GLEngine::InputManager _inputManager;
	GLEngine::FpsLimiter _fpsLimiter;

	float _maxfps;
	float _fps;

	float _time;
};

