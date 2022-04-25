#pragma once
#include <SDL.h>
#include "Color.h"
#include "World.h"
#include "Graphics.h"
#include "FrameTimer.h"

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
	const float frameRate = 75.0f ;
	const float secPerFrame = 1.0f / frameRate;

	Graphics gfx;
	World colony;
};