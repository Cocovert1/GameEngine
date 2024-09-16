#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Bengine/Sprite.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/GLTexture.h>
#include <Bengine/Window.h>
#include <Bengine/Bengine.h>
#include <Bengine/Camera2D.h>

#include <Bengine/SpriteBatch.h>

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

	Bengine::Window _window;
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
	//std::vector <Bengine::Sprite*> _sprites; //Deprecated

	Bengine::GLSLProgram _colorProgram;
	Bengine::Camera2D _camera;

	Bengine::SpriteBatch _spriteBatch;

	float _fps;
	float _frameTime;
	float _maxfps;

	float _time;
};

