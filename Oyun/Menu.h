#pragma once
#include "SDL/SDL.h"
#include <map>
#include <string>
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <SDL/SDL_image.h>
#include <iostream>

using namespace std;

class Menu 
{
public:
	Menu(); // Default Constructor
	Menu(const Menu& pMenu);
	Menu& operator = (const Menu& pMenu);
	~Menu();

	void loadMenu(char* , SDL_Renderer*);
	bool loadPathMenu(char* , string , SDL_Renderer*);
	void loadMenuItems(SDL_Renderer*);
	void eventHandling();	
	void renderMenu(SDL_Renderer*);

	static Menu* getInstanceMenu();

private:
	static Menu* mInstanceMenu;

	TTF_Font * mMenuFont;
	Mix_Music* mMenuMusic;

	SDL_Rect mMouseCoord;
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