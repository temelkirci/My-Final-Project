#pragma once
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Maps.h"
#include "Inventory.h"
#include "Player.h"

class GameObjects : public Maps, public Inventory
{
public:
	GameObjects(); // Default Constructor
	GameObjects(const GameObjects& pGameLoop);
	GameObjects& operator = (const GameObjects& pGameLoop);
	~GameObjects();

	void gameLoop(SDL_Renderer* pRenderer);
	void loadGameObjects(SDL_Renderer* pRenderer);

private:
};