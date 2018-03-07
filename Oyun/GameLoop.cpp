#include "GameLoop.h"

GameLoop::GameLoop()
{

}

GameLoop::GameLoop(const GameLoop& pGameLoop)
{

}

GameLoop& GameLoop::operator = (const GameLoop& pGameLoop)
{
	return *this;
}

GameLoop::~GameLoop()
{

}

GameLoop* GameLoop::getInstanceGameLoop()
{
	if (mInstanceGameLoop == 0)
		mInstanceGameLoop = new GameLoop();

	return mInstanceGameLoop;
}

void GameLoop::Loop(SDL_Renderer* pRenderer) 
{
	while (GameState != GAME_STATE::PLAYING) // Oyundan çýkýþ yapýlana kadar sürekli çiz
	{
		Render(pRenderer);
		//events();
	}
}