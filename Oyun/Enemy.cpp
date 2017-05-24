#include <iostream>
#include "SDL/SDL.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <SDL/SDL_image.h>

Enemy :: Enemy()
{
	srand ((unsigned int)time(0));

	meteor_rect.x = -100;
	meteor_rect.y = rand() % 500;
	meteor_rect.w = 50;
	meteor_rect.h = 50;

	meteor_x = meteor_rect.x;
	meteor_y = meteor_rect.y;

	meteor_range = rand() % 500;
	meteor_health = 100;
	delay_time = 200;
	current_time = 0;

	index = 0;
	
	enemy_array[0] = "small_meteor_1";
	enemy_array[1] = "small_meteor_2";
	enemy_array[2] = "small_meteor_3";
	enemy_array[3] = "small_meteor_4";
	enemy_array[4] = "small_meteor_5";
	enemy_array[5] = "small_meteor_6";
	enemy_array[6] = "small_meteor_7";
	enemy_array[7] = "small_meteor_8";
	enemy_array[8] = "small_meteor_9";
	enemy_array[9] = "small_meteor_10";
	enemy_array[10] = "small_meteor_11";
	enemy_array[11] = "small_meteor_12";
	enemy_array[12] = "small_meteor_13";
	enemy_array[13] = "small_meteor_14";
	enemy_array[14] = "small_meteor_15";
	enemy_array[15] = "small_meteor_16";
	
}

Enemy :: ~Enemy()
{

}

void Enemy :: load_enemy(string file_path, char* enemy_picture , SDL_Renderer* render)
{
	SDL_Surface* surface_enemy = IMG_Load(file_path.c_str());
	if(surface_enemy == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Enemy" , "Enemy yuklenemedi..!" , NULL);
		exit(0);
	}

	SDL_Texture* texture_enemy = SDL_CreateTextureFromSurface(render , surface_enemy);
	SDL_FreeSurface(surface_enemy);

	if(texture_enemy != 0)
	{
		enemy_map[enemy_picture] = texture_enemy; 
	}
}

// düþman L þeklinde hareket edecek
void Enemy :: draw_enemy(SDL_Renderer* rend , Uint32 real_time , int camx , int camy)
{
	if((meteor_health > 0) && (meteor_rect.x <= meteor_range))
	{
		meteor_rect.x = (meteor_x + camx);
		meteor_rect.y = (meteor_y + camy);

		if(current_time == 0)
			current_time = real_time + delay_time;

		if(real_time <= current_time)
		{
			bool loop = true;
			if(loop)
			{
				meteor_x = meteor_x + 1;		
				loop = false;
			}
			SDL_RenderCopyEx(rend , enemy_map[enemy_array[index]] , NULL , &meteor_rect , NULL , 0 , SDL_FLIP_NONE);
		}
		else
		{

			current_time = real_time + delay_time;
			if(index == 15)
				index = 0;
			else
				index++;

			SDL_RenderCopyEx(rend , enemy_map[enemy_array[index]] , NULL , &meteor_rect , NULL , 0 , SDL_FLIP_NONE);
		}
	}
	else
	{
		meteor_rect.x = (meteor_x + camx);
		meteor_rect.y = (meteor_y + camy);

		meteor_health = 100;

		meteor_rect.x = -100;
		meteor_rect.y = rand() % 500;

		meteor_x = -100;
		meteor_y = rand() % 500;

		meteor_range = rand() % 500 + 700;
	}
	
}
void Enemy :: enemy_load(SDL_Renderer* renderer)
{
	load_enemy("assets/small_meteor/a10000.png", "small_meteor_1", renderer);
	load_enemy("assets/small_meteor/a10001.png", "small_meteor_2", renderer);
	load_enemy("assets/small_meteor/a10002.png", "small_meteor_3", renderer);
	load_enemy("assets/small_meteor/a10003.png", "small_meteor_4", renderer);
	load_enemy("assets/small_meteor/a10004.png", "small_meteor_5", renderer);
	load_enemy("assets/small_meteor/a10005.png", "small_meteor_6", renderer);
	load_enemy("assets/small_meteor/a10006.png", "small_meteor_7", renderer);
	load_enemy("assets/small_meteor/a10007.png", "small_meteor_8", renderer);
	load_enemy("assets/small_meteor/a10008.png", "small_meteor_9", renderer);
	load_enemy("assets/small_meteor/a10009.png", "small_meteor_10", renderer);
	load_enemy("assets/small_meteor/a10010.png", "small_meteor_11", renderer);
	load_enemy("assets/small_meteor/a10011.png", "small_meteor_12", renderer);
	load_enemy("assets/small_meteor/a10012.png", "small_meteor_13", renderer);
	load_enemy("assets/small_meteor/a10013.png", "small_meteor_14", renderer);
	load_enemy("assets/small_meteor/a10014.png", "small_meteor_15", renderer);
	load_enemy("assets/small_meteor/a10015.png", "small_meteor_16", renderer);
}