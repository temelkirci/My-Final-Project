#include <SDL/SDL.h> 
#include <string>
#include <iostream>

#include "Game.h"

#define SCREEN_W�DTH  1366
#define SCREEN_HEIGHT  768

int main(int argc, char** argv) 
{
	Game *pGame = new Game();

	if ( pGame->initializeGame("TEMEL KIRCI", 10, 30, SCREEN_W�DTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE) )
	{
		pGame->startApplication();
	}
	else
	{
		SDL_Quit(); // T�m SDL sistemlerini kapat
		delete pGame;
	}

	// quit
	SDL_Quit(); // T�m SDL sistemlerini kapat

	// clean
	delete pGame;

    return 0;
}
