#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <map>

using namespace std;

class Animation
{
public :
	Animation();
	~Animation();

	SDL_Rect temp;
	SDL_Rect lamp_rect;
	SDL_Rect fire_rect;
	SDL_Rect water_rect;

	void Lamp(SDL_Renderer* , int , int);
	void Fire(SDL_Renderer*);
	void Water(SDL_Renderer*);
	void load_animation(SDL_Renderer*);

	bool load_anime(string , string , SDL_Renderer*);
	map<string , SDL_Texture*> map_animation; // ilk deðiþken string , ikinci deðiþken Texture tutan bir deðiþken
	tuple<string , // light name
		  bool , // draw active or passive
		  int , // unique index
		  SDL_Rect, // light coordinate
		  SDL_Rect> // light scope
		light[10];
};