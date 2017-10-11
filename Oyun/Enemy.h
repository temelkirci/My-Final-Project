#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <map>
#include <string>

using namespace std;

class Enemy
{
public:

	Enemy();
	~Enemy();

	//Uint32 delay_time;
	//Uint32 current_time;
	Uint32 airplane_time;
	SDL_Rect airplane_rect;

	Uint32 creature_time;
	SDL_Rect creature_rect;
	int creature_health;
	void drawHelicopter(SDL_Renderer*);
	
	void drawAirplane(SDL_Renderer* , int , int , Uint32);
	void drawCreature(SDL_Renderer* , int , int , Uint32);

	void enemy_load(SDL_Renderer*);
	void load_enemy(char* , char* , SDL_Renderer*);
	
private:
	map<string , SDL_Texture*> enemy_map;
};