#include "World.h"
#include "Game.h"
#include <iostream>

Game::Game(const char* title, int setX, int setY, bool fullscreen)
	:
	gfx(title, setX, setY, fullscreen),
	colony(1000,0.4f,0.15f,8,0.99f)
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
	tickCounter += frame.Mark();
	if (tickCounter > secPerFrame) {
		std::cout << "FPS: " << 1.0f / tickCounter << std::endl;
		colony.Update();
		tickCounter = 0;
	}
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

