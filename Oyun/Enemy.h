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
	string trex_array[5];
	string trex_direction;
	int index;

	struct Meteor
	{
		
	} _mMeteor[10];

	int trex_health;
	int trex_x;
	int trex_y;
	SDL_Rect trex_rect;
	double trex_angle;

	int meteor_health;
	int meteor_range;
	int meteor_x;
	int meteor_y;
	int index_trex;

	Uint32 delay_time;
	Uint32 current_time;

	Uint32 trex_current_time;
	Uint32 trex_delay_time;
	Uint32 trex_dead_time;
	Uint32 trex_walk_time;
	Uint32 trex_walk_delay_time;

	bool trex_dead;
	SDL_Rect meteor_rect;
	void enemy_load(SDL_Renderer*);
	void load_enemy(string , char* , SDL_Renderer*);
	void draw_enemy(SDL_Renderer* , Uint32 , int , int);
	void draw_trex(SDL_Renderer* , Uint32 , int* , int* , double , int , int);
private:
	map<string , SDL_Texture*> enemy_map;
};