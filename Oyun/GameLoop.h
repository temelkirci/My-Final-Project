#pragma once
#include "Inventory.h"

class GameLoop : public Inventory
{
public:
	GameLoop(); // Default Constructor
	GameLoop(const GameLoop& pGameLoop);
	GameLoop& operator = (const GameLoop& pGameLoop);
	~GameLoop();

	void Loop(SDL_Renderer*);

	enum class GAME_STATE
	{
		OPENING,    // Application is preparing for Menu
		MENU,       // In Menu
		STARTING,   // Game Background is preparing
		PLAYING,    // The game has started
		WAITING,    // Pause
		GAME_OVER,  // The game has finished
		EXIT	    // Exit
	}GameState;

	static GameLoop* getInstanceGameLoop();
private:
	static GameLoop* mInstanceGameLoop;
};