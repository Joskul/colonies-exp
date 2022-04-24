#include "Graphics.h"
#include <iostream>

Graphics::Graphics(const char* title, int setX, int setY, bool fullscreen)
{
	int flags(0);
	flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialized" << std::endl;

		win = SDL_CreateWindow(title, setX, setY, screenWidth, screenHeight, flags);
		if (win) {
			std::cout << "Window Created" << std::endl;
		}

		ren = SDL_CreateRenderer(win, -1, 0);
		if (ren) {
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	}
	else { isRunning = false; }
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	std::cout << "Session Terminated" << std::endl;
}

void Graphics::putPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(ren, r, g, b, a);
	SDL_RenderDrawPoint(ren, x, y);
}

void Graphics::putPixel(int x, int y, Color c)
{
	putPixel(x, y, c.r, c.g, c.b, c.a);
}

bool Graphics::valid() const
{
	return isRunning;
}

void Graphics::terminate()
{
	isRunning = false;
}

void Graphics::renderClear()
{
	SDL_RenderClear(ren);
}

void Graphics::renderPresent()
{
	SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, 255);
	SDL_RenderPresent(ren);
}