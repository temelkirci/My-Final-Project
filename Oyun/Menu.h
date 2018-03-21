#pragma once
#include "SDL/SDL.h"
#include <map>
#include <string>
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include "Events.h"

using namespace std;

class Menu : public Events
{
public:
	Menu(); // Default Constructor
	Menu(const Menu& pMenu);
	Menu& operator = (const Menu& pMenu);
	~Menu();

	void loadMenu(char* , SDL_Renderer*);
	bool loadPathMenu(char* , string , SDL_Renderer*);
	void loadMenuFiles(SDL_Renderer*);
	void eventHandling();	
	void renderMenu(SDL_Renderer*);

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


private:

	TTF_Font * mMenuFont;
	Mix_Music* mMenuMusic;

	SDL_Rect mMenuMouseCoord;
	SDL_Rect mMenuBackgroundRect;

	SDL_Color mMenuColor;
	SDL_Color mTextColor;

	char* mButtonArray[5];
	SDL_Rect mStartButton;
	SDL_Rect mResumeButton;
	SDL_Rect mCreditsButton;
	SDL_Rect mSaveButton;
	SDL_Rect mExitButton;
	SDL_Rect mLoadButton;

	map<string, SDL_Texture*> mButtonMap;

	SDL_Texture* mMenuTexture;
	SDL_Texture* mButtonTexture;
};