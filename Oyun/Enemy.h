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

	string enemy_array[16];
	string trex_array[5];
	string trex_direction;
	int index;

	string trex_status;

	double trex_health;
	int trex_x;
	int trex_y;
	SDL_Rect trex_rect;
	Mix_Chunk *trex_roar;
	double walk_angle;
	double real_angle;

	double x_dis;
	double y_dis;
	double trex_tanjant;

	int meteor_health;
	int meteor_range;
	int meteor_x;
	int meteor_y;
	int index_trex;
	int trex_speed;

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