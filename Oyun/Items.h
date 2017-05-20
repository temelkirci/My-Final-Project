#pragma once
#include "SDL/SDL.h"
#include "Window.h"
#include <tuple>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Items : public Window
{
public:
	Items();
	~Items();
	
	int Collectible_Size;
	int Uncollectible_Size;
	int Solid_Size;

	struct Item 
	{
		string item_name;
		string item_blendmode;
		int item_id;
		int number_item;
		int item_health;
		bool item_active;
		SDL_Rect item_rect;
		SDL_Texture* item_texture;
		
	} *Collectible_Items , *Uncollectible_Items , *Solid_Items;

	void item_information(SDL_Renderer* , string);

	SDL_Rect temp_rect;
	string inf;
private:
	
};