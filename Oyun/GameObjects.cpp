#include "GameObjects.h"

GameObjects::GameObjects()
{

}

GameObjects::GameObjects(const GameObjects& pGameLoop)
{

}

GameObjects& GameObjects::operator = (const GameObjects& pGameLoop)
{
	return *this;
}

GameObjects::~GameObjects()
{

}

void GameObjects::loadGameObjects(SDL_Renderer* pRenderer)
{
	loadMaps(pRenderer);
	loadInventoryFiles(pRenderer);
	loadPlayer(pRenderer);
}

void GameObjects::gameLoop(SDL_Renderer* pRenderer)
{
	SDL_RenderClear(pRenderer); // renderi temizle
	double startFPS = SDL_GetTicks();

	drawMap(pRenderer);	
	drawInventory(pRenderer);
	drawMapObjects(pRenderer);
	playerInformation(pRenderer);

	drawCursor(pRenderer);
	
	double endFPS = SDL_GetTicks();
	double elapsedTime = endFPS - startFPS;

	cout << elapsedTime << endl;

	if(elapsedTime != 0)
		//cout << 1000.0 / elapsedTime << endl;

	SDL_RenderPresent(pRenderer);
}