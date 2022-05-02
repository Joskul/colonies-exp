#pragma once
#include <SDL.h>
#include "Color.h"

class Graphics {
public:
	Graphics(const char* title, int setX, int setY, bool fullscreen = false);
	~Graphics();
	void putPixel(const int x, const int y, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 255);
	void putPixel(const int x, const int y, const Color c);

	void drawCircle(const int x, const int y, const float radius, const Color c);
	void drawLine(const int x1, const int y1, const int x2, const int y2, const Color c);

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