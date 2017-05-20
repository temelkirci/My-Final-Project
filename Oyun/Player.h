#pragma once
#include <SDL/SDL.h>
#include <string>
#include <map>
#include "Timer.h"
#include "Tools.h"
#include "Animation.h"

using namespace std;
const int MAX_HEALTH = 100;

class Player : public Timer , public Tools , public Animation
{
public:
	Player();
	~Player();

	bool barbaros_yukle_weapon(string , SDL_Renderer*,char*);

	void barbaros_�iz(SDL_Renderer* , string , int* , int* , int , int ,string , Uint32);
	void barbaros_g�ncelle(SDL_Renderer* , Uint32);
	void load_barbaros(SDL_Renderer*);
	void player_information(SDL_Renderer*);

	Uint32 player_time;
	Uint32 hunger_time;
	Uint32 thirsty_time;

	int x_hedef;
	int y_hedef;

	int thirtsy;
	int hunger;
	int attack_power;
	int health;

	int handgun_mermi;
	int rifle_mermi;
	int shotgun_mermi;
	
	bool oyun_baslat;

	int arti_x_speed;
	int eksi_x_speed;
	int arti_y_speed;
	int eksi_y_speed;

	string direction_bullet;
	string barbaros_durum;
	string barbaros_guns;

	int xpoz;
	int ypoz;
	double angle;
	int speed;

	bool active_bullet;

	SDL_Color playerColor;
	SDL_Rect player_barbaros;
	SDL_Rect information;
	SDL_Surface* surface_barbaros;
	SDL_Texture* texture_barbaros;
	SDL_Point playerPoint;
	
private:
	
	map<string , SDL_Texture*> barbaros_weapon;
};
