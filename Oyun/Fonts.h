#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <map>
#include <SDL/SDL_image.h>
#include <iostream>

using namespace std;

class Fonts 
{
public:

	Fonts(); // Default Constructor
	Fonts(const Fonts& pFonts);
	Fonts& operator = (const Fonts& pFonts);
	~Fonts();

	// hepsi silinecek/yerdeðiþtirecek
	void loadFonts(SDL_Renderer* pRenderer);
	int loadImage(char* pPathFile, string pImageName, SDL_Renderer* pRenderer);
	void playerStatus(SDL_Renderer* pRenderer, int pX, int pY, int pWidth, int pHeight, int pHealth, int pBullet, int pHungry, int pThirtsy);
	void writeText(SDL_Renderer* pRenderer, Uint32 pTime, char* pText);

private:

	TTF_Font * mFont;
	SDL_Texture* mTextTexture;
	SDL_Color mBackColor; // arkaplan beyaz olacak

	SDL_Rect mBackRect;
	SDL_Rect mHungerRect; // 0-100 piksel arasýnda olacak
	SDL_Rect mThirstyRect; // 0-100 piksel arasýnda olacak
	SDL_Rect mHealthRect; // 0-100 piksel arasýnda olacak

	double total;

	SDL_Texture* mImageTexture;

	map<string, SDL_Texture*> mImageMap;

	SDL_Rect arkaPlan;
	Uint32 toplam;	
	char* dizi[4];
};