#pragma once
#include <SDL.h>
#include "Color.h"
#include "World.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "InputHandler.h"

class Game {
public:
	Game(const char* title, int setX, int setY, bool fullscreen = false);
	~Game();

	void handleEvents();
	void updateModel();
	void drawModel();

	bool running();
private:
	FrameTimer frame;

	SDL_Event event;

	Graphics gfx;
	World colony;
	Input input;
};