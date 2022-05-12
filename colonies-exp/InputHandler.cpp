#include "InputHandler.h"

Input::Input(SDL_Event& event)
	:
	mouse(event),
	key(event)
{
}

Input::~Input()
{
}

Input::Keyboard::Keyboard(SDL_Event& event)
	:
	event(event)
{
}

bool Input::Keyboard::isPressed(Uint32 key)
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

Input::Mouse::Mouse(SDL_Event& event)
	:
	event(event)
{
}

bool Input::Mouse::isPressed(int key)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == key) {
		mouseState[key] = state::keyDown;
		return true;
	}
	else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == key) {
		mouseState[key] = state::keyUp;
		return false;
	}
	return mouseState[key] == state::keyDown;
}

Vec2<int> Input::Mouse::getMousePos()
{
	if (event.type == SDL_MOUSEMOTION) {
		mousePos = { event.motion.x, event.motion.y };
	}
	return mousePos;
}

Vec2<int> Input::Mouse::getWheelPos()
{
	return wheelPos;
}

int Input::Mouse::wheelY()
{
	if (event.type == SDL_MOUSEWHEEL) {
		wheelPos.y += event.wheel.y;
		return event.wheel.y;
	}
	return 0;
}
