#pragma once
#include "SDL/SDL.h"
#include <map>
#include <string>

using namespace std;

class Enemy
{
public:

	Enemy();
	~Enemy();

	string enemy_array[16];
	int index;

	struct Meteor
	{
		
	} _mMeteor[10];

	int meteor_health;
	int meteor_range;
	int meteor_x;
	int meteor_y;
	Uint32 delay_time;
	Uint32 current_time;
	SDL_Rect meteor_rect;
	void enemy_load(SDL_Renderer*);
	void load_enemy(string , char* , SDL_Renderer*);
	void draw_enemy(SDL_Renderer* , Uint32 , int , int);
private:
	map<string , SDL_Texture*> enemy_map;
};