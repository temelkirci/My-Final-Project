#pragma once
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include <tuple>
#include <map>

using namespace std;
 
class Window 
{
public:
	Window();
	~Window();

	bool statu_inventory;
	bool statu_crafting;
	int x_window , y_window ;
	int w_window , h_window ;

	int x_crafting , y_crafting , w_crafting , h_crafting;
	bool complete_crafting;
		       
	tuple<string , // item name 
		  SDL_Texture* , 
		  bool ,  // slot empty ?
		  int , // item number
		  SDL_Rect> Slot1;

	tuple<string , SDL_Texture* , bool  , int , SDL_Rect> Slot2;
	tuple<string , SDL_Texture* , bool  , int , SDL_Rect> finalSlot;
	map<string , SDL_Texture*> all_textures;

	SDL_Rect final_rect;
	SDL_Rect slot1_rect;
	SDL_Rect slot2_rect;

	SDL_Texture* window_texture;
	SDL_Texture* crafting_texture;
	SDL_Rect crafting_coord;
	void information_window(SDL_Renderer* , Uint32);
	void crafting(SDL_Renderer*);
	void load_inf(SDL_Renderer*);
private:
	SDL_Texture* window_background;
};