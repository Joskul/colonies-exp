#include "InputHandler.h"

Input::Input(SDL_Event& event)
	:
	event(event)
{
}

Input::~Input()
{
}

bool Input::keyIsPressed(Uint32 key)
{
	if (event.type == SDL_KEYDOWN && key == event.key.keysym.sym) {
		keyState[key] = state::keyDown;
		return true;
	}
	else if (event.type == SDL_KEYUP && key == event.key.keysym.sym) {
		keyState[key] = state::keyUp;
		return false;
	}

	return keyState[key] == state::keyDown;
}
