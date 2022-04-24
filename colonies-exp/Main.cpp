#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game("Colony Simulation", 100, 100);

	while (game->running()) {
		game->handleEvents();
		game->updateModel();
		game->drawModel();
	}

	delete game;

	return 0;
}