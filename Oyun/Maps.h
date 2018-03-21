#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <map>
#include <SDL/SDL_image.h>
#include <iostream>
#include "Player.h"

using namespace std;

class Maps : public Player
{
public:
	Maps();
	~Maps();

	void drawMap(SDL_Renderer* pRenderer);
	void drawMapObjects(SDL_Renderer* pRenderer);
	void loadMaps(SDL_Renderer* pRenderer);
	void drawCursor(SDL_Renderer* pRenderer);
	void loadMapFiles(char* pMapFilePath, SDL_Renderer* pRenderer, char* pMapName);

	double getMapPositionX();
	double getMapPositionY();
	double getCameraPositionX();
	double getCameraPositionY();

	double getMousePositionX();
	double getMousePositionY();

	SDL_Rect getMouseRect();
	string mCurrentCursor;
protected:
	SDL_Rect mMouseRect;
	SDL_Rect mSolidMouse;

private:
	map<string, SDL_Texture*> mMapsMap;
	
	SDL_Rect mMainCameraRect;
	SDL_Rect mMainMapRect;
	
};