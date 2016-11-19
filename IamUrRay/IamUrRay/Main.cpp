#include "Game.h"
#include <iostream>
#include <SDL_error.h>

using namespace std;

int main(int argc, char* argv[])
{

	
	Game* game = new Game();
	game->run();

	delete game;
	return 0;
}