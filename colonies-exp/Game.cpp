#include "World.h"
#include "Game.h"
#include <iostream>

Game::Game(const char* title, int setX, int setY, bool fullscreen)
	:
	gfx(title, setX, setY, fullscreen)
{
}

Game::~Game()
{
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		gfx.terminate();
		break;

	default:
		break;
	}
}

void Game::updateModel()
{
	const float deltaTime = frame.Mark();
	colony.Update(deltaTime);

	std::cout << "FPS: " << 1 / deltaTime << std::endl;
}

void Game::drawModel()
{
	gfx.renderClear();
	//draw stuff here

	colony.Draw(gfx);

	gfx.renderPresent();
}

bool Game::running()
{
	return gfx.valid();
}

