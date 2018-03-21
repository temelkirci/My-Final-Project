#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Texture
{
public:
	Texture();
	~Texture();

	void loadTextures(SDL_Renderer* pRenderer);
	void loadBackground(char* , SDL_Renderer* pRenderer);
	bool load(char* , string , SDL_Renderer* pRenderer);
	void itemInformation(SDL_Renderer* pRenderer, string);
	void drawObject(SDL_Renderer* pRenderer, Uint32);
	void draw_texture(SDL_Renderer* pRenderer);
	void drawSolidTexture(SDL_Renderer* pRenderer);
	void drawCamera(SDL_Renderer* pRenderer, double , double , int , int);
	void drawBullet(SDL_Renderer* pRenderer, double , double);

	//bool randomPosition(int , int , Item&);
	void tank(SDL_Renderer* pRenderer, int, int);

private:
	map<string, SDL_Texture*> mTextureMap; // ilk deðiþken string , ikinci deðiþken Texture tutan bir deðiþken
	SDL_Surface* mSurface;
	SDL_Rect mCamera;
	//SDL_Surface* sur_bck;
	SDL_Surface* mBackgroundSurface;
	SDL_Texture* mTexture;
	bool mIsObjectCollision;
	string mevcut_mermi;
	int z;
	int mMapRow;
	int mMapColumn;
	int mMapX;
	int mMapY;

	SDL_Rect mMapRect;
};
