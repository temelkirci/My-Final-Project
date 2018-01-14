#pragma once
#include "SDL/SDL.h"
#include "Window.h"
#include <string>
#include <vector>

using namespace std;

class Items : public Window
{
public:
	Items();
	~Items();
	
	void setColItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	void setUncolItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	void setSolidItems(string , string , int , int , bool , SDL_Rect , SDL_Texture*);
	
	struct Item 
	{
		string item_name;
		string item_blendmode;
		int number_item;
		int item_health;
		bool item_active;
		SDL_Rect item_rect;
		SDL_Texture* item_texture;

	}esya;

	void item_information(SDL_Renderer* , string);

	vector<Item> solid;
	vector<Item> col;
	vector<Item> uncol;

	struct bullet 
	{
		string bullet_name;
		bool bullet_active;
		SDL_Rect bullet_rect;
		SDL_Texture* bullet_texture;
		
	}bullet_handgun , bullet_rifle , bullet_shotgun;

	vector<SDL_Rect> rect; // tüm nesnelerin koordinatlarýný saklar

	string inf;
private:
	
};