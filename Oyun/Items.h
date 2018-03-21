#pragma once
#include "SDL/SDL.h"
#include <string>
#include <vector>

using namespace std;

class Items 
{
public:
	Items();
	Items(const Items& pItems);
	Items& operator = (const Items& pItems);
	~Items();
	
	void setCollectibleItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	void setUnCollectibleItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	void setSolidItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	
	struct ItemStruct 
	{
		string itemName;
		string itemBlendMode;
		int itemNumber;
		int itemHealth;
		bool itemActive;
		SDL_Rect itemRect;
		SDL_Texture* itemTexture;

	}item;

	void itemInformation(string pInformation);

	struct bullet 
	{
		string bulletName;
		bool bulletActive;
		SDL_Rect bulletRect;
		SDL_Texture* bulletTexture;
		
	}bulletHandgun , bulletRifle , bulletShotgun;

private:

	vector<ItemStruct> mSolidVector;
	vector<ItemStruct> mCollectibleVector;
	vector<ItemStruct> mUnCollectibleVector;

	vector<SDL_Rect> mItemRectVector; // tüm nesnelerin koordinatlarýný saklar
	string mInformation;
};