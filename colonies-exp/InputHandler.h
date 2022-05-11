#pragma once
#include <SDL.h>
#include <vector>

class Input {
public:
	Input(SDL_Event& event);
	~Input();
	bool keyIsPressed(Uint32 key);
private:
	enum class state {
		keyDown,
		keyUp
	};
private:
	SDL_Event& event;
	std::vector<state> keyState = {state::keyUp};
};