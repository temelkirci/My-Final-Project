#pragma once
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Menu.h"

class Game : public Menu
{
public:
	Game(); // Default Constructor
	Game(const Game& pGame); // Copy Constructor
	Game& operator = (const Game& pGame); // Copy assingment Operator
	~Game();  // Destructor

	// Member Functions
	bool initializeGame(const char*,int,int,int,int,int);
	void startApplication();

private:
	SDL_Renderer* mRenderer; // do it static
	SDL_Window* mMainWindow ;
};
