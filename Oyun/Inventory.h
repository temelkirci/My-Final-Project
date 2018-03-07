#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
	void updateInventory(SDL_Renderer* pRenderer);
	void addItemtoInventory(string pItemName, int pItemNumber, SDL_Texture* pTexture);
	void deleteItem(string pObjectName , int pItemNumber);

	static Inventory* getInstanceInventory();

private:
	static Inventory* mInstanceInventory;
	SDL_Texture * mInventoryTexture; // envanter resmi
	int mInventoryItemNumber; // envanterdeki farklý eþya sayýsý
	SDL_Color mInventoryColor;

	struct InventoryItem
	{
		string nameItem; // eþyanýn adý
		SDL_Texture* textureItem; // eþya texture
		int numberItem; // eþya sayýsý
		int xCoordItem; // esya çizim koordinatý x ekseni
		int yCoordItem; // esya çizim koordinatý y ekseni
	}mItemInventory;

	vector <InventoryItem> ItemVector;

	map<string, SDL_Texture*> envanter_draw;
	string envanter_durum;
	int mMaximumInventoryItemCapacity; // envanterin maksimum kapasitesi
	SDL_Rect mRectInventory;
};
