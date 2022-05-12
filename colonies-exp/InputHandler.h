#pragma once
#include <SDL.h>
#include <vector>
#include "Vec2.h"

class Input {
public:
	Input(SDL_Event& event);
	~Input();

private:
	enum class state {
		keyUp,
		keyDown
	};
private:
	class Mouse {
	public:
		Mouse(SDL_Event& event);
		bool isPressed(int key);
		Vec2<int> getMousePos();
		Vec2<int> getWheelPos();
		int wheelY();
	private:
		std::vector<state> mouseState = { state::keyUp };
		Vec2<int> mousePos{ 0,0 };
		Vec2<int> wheelPos{ 0,0 };
		SDL_Event& event;
	};

	class Keyboard {
	public:
		Keyboard(SDL_Event& event);
		bool isPressed(Uint32 key);
	private:
		std::vector<state> keyState = { state::keyUp };
		SDL_Event& event;
	};

public:
	Mouse mouse;
	Keyboard key;
};