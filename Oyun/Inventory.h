#pragma once
#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include <map>
#include <tuple>
#include "Fonts.h"

using namespace std;

class Inventory : public Fonts 
{
public:
	Inventory();
	~Inventory();

	void Envanter_Yukle(char* , string , SDL_Renderer*);
	void Envanter_Çiz(string , int , int , int , int , SDL_Renderer*);
	void Envanter_Güncelle(SDL_Renderer*);
	void loadInventory(SDL_Renderer*);
	void Esya_Ekle(string , int , SDL_Renderer* , SDL_Texture*);
	void Envanter(SDL_Renderer*);
	void informationItem(SDL_Renderer*);
	void deleteItem(string , int);

	SDL_Rect box;
	string infItem;
	int inventory_size; // envanterdeki farklý eþya sayýsý
	SDL_Color envanter_color;

	SDL_Color inventory_color;

	struct Envanter
	{
		SDL_Rect InventoryRect;
		SDL_Texture* InventoryTexture;
		bool OpenInventory;
	}InventoryStore;

	struct InventoryObjects
	{
		string objectName; // esyanýn adý
		SDL_Texture* objectTexture; // esya texture
		int objectNumber; // nesne sayýsý
		int xCoord; // esya koordýnat
		int yCoord;

	}InventoryObject[18];
	
	map<string , SDL_Texture*> envanter_draw;
	string envanter_durum ;
	int max_envanter; // envanterin maksimum kapasitesi
	SDL_Rect rect_inventory;

private:
	SDL_Texture* envanter_texture; // envanter resmi
	SDL_Texture* adet_texture;
};