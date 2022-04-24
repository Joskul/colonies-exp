#pragma once
#include <SDL.h>
#include "Color.h"

class Graphics {
public:
	Graphics(const char* title, int setX, int setY, bool fullscreen = false);
	~Graphics();
	void putPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void putPixel(int x, int y, Color c);

	bool valid() const;
	void terminate();

	void renderClear();
	void renderPresent();
private:
	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	Color bgColor = Colors::Black;

	static constexpr int screenWidth = 1280;
	static constexpr int screenHeight = 720;

	bool isRunning = false;
};