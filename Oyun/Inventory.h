#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Inventory
{
public:
	Inventory();
	Inventory(const Inventory& pInventory); // Copy Constructor
	Inventory& operator = (const Inventory& pInventory); // Copy assingment Operator
	~Inventory();

	void loadInventoryFiles(SDL_Renderer* pRenderer);
	void loadInventory(const char* pPathFile, const char* pInventoryFiles , SDL_Renderer* pRenderer);
	void drawInventory(SDL_Renderer* pRenderer);
	void addItemtoInventory(string pItemName, int pItemNumber, SDL_Texture* pTexture);
	void deleteItem(string pObjectName , int pItemNumber);

	SDL_Rect getInventoryRect();
	int getInventoryMaxSize();
	int getInventoryCurrentSize();

protected:
	struct InventoryItem
	{
		string nameItem; // eþyanýn adý
		SDL_Texture* textureItem; // eþya texture
		int numberItem; // eþya sayýsý
		SDL_Rect itemPositionRect;
	}mItemInventory;

	vector <InventoryItem> ItemVector;
private:
	
	SDL_Texture * mInventoryTexture; // envanter resmi
	SDL_Texture* tTextTexture;
	int mInventoryItemNumber; // envanterdeki farklý eþya sayýsý
	SDL_Color mInventoryColor;
	TTF_Font* mInventoryFont;

	map<string, SDL_Texture*> mInventoryMap;
	string envanter_durum;
	int mMaximumInventoryItemCapacity; // envanterin maksimum kapasitesi
	SDL_Rect mInventoryRect;
};
