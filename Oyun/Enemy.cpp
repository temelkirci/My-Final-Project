#include <iostream>
#include "SDL/SDL.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL/SDL_image.h>
#include "SDL/SDL_mixer.h"

#define PI 3.14159265

Enemy :: Enemy()
{
	srand ((unsigned int)time(0));

	meteor_rect.x = -100;
	meteor_rect.y = rand() % 1400;
	meteor_rect.w = 50;
	meteor_rect.h = 50;

	meteor_x = meteor_rect.x;
	meteor_y = meteor_rect.y;

	trex_speed = 10;

	trex_rect.x = rand() % 5000;
	trex_rect.y = rand() % 1200;
	trex_rect.w = 200;
	trex_rect.h = 70;

	trex_x = trex_rect.x;
	trex_y = trex_rect.y;

	trex_health = 300.0;
	trex_current_time = 0;
	trex_delay_time = 700;
	trex_dead_time = 0; // yerde ölü bekleme süresi
	trex_walk_delay_time = 100;
	trex_walk_time = 0;

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3072) < 0 )
						cout<<"Mix_OpenAudio yüklenemedi "<<Mix_GetError()<<endl;
	trex_roar = Mix_LoadWAV("assets/sounds/trex_roar.mp3");

	walk_angle = 0;
	real_angle = 0;
	trex_dead = false;
	index_trex = 2;
	trex_direction = "";
	meteor_range = rand() % 1000;
	meteor_health = 100;
	delay_time = 200;
	current_time = 0;
	trex_status = "move";
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
	
	trex_array[0] = "trex_a_1";
	trex_array[1] = "trex_a_2";
	trex_array[2] = "trex_a_3";
	trex_array[3] = "trex_a_4";
	trex_array[4] = "trex_a_5";
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
		meteor_rect.y = rand() % 1200;

		meteor_x = rand() % 5000;
		meteor_y = rand() % 1400;

		meteor_range = rand() % 500 + 500;
	}
	
}

void Enemy :: draw_trex(SDL_Renderer* rend , Uint32 real_time , int *pozx , int *pozy , double barbaoros_angle , int camx , int camy)
{
	SDL_Rect player_rect;
	player_rect.x = *pozx + camx;
	player_rect.y = *pozy + camy;
	player_rect.w = 100;
	player_rect.h = 100;

	if(trex_health > 0.0)
	{
		
		if(trex_current_time == 0)
			trex_current_time = real_time + trex_delay_time;

		if(real_time <= trex_current_time)
		{
			///// TREX AÇI /////
			if((player_rect.x+50) >= (trex_rect.x + 100)) // trex solda
			{
				if((player_rect.y + 50) >= (trex_rect.y + 25)) // sol-üst
				{
					x_dis = abs((player_rect.x+50) - (trex_rect.x + 100));
					y_dis = abs((player_rect.y+50) - (trex_rect.y + 25));
				
					if(x_dis == 0)
					{
						real_angle = 90;
						walk_angle = 0;
					}
					else if(y_dis == 0)
					{
						real_angle = 0;
						walk_angle = 0;
					}
					else
					{
						trex_tanjant = y_dis / x_dis;
						walk_angle = (atan(trex_tanjant) * 180) / PI ;
						real_angle = walk_angle;
					}
					
					trex_direction = "sol ust";
				}
				else // sol-alt
				{
					x_dis = abs((player_rect.x+50) - (trex_rect.x + 100));
					y_dis = abs((trex_rect.y + 25) - (player_rect.x + 50));

					if(x_dis == 0)
					{
						walk_angle = 0;
						real_angle = 270;
					}
					else if(y_dis == 0)
					{
						walk_angle = 0;
						real_angle = 0;
					}
					else
					{
						trex_tanjant = y_dis / x_dis;
						walk_angle = (atan(trex_tanjant) * 180) / PI ;
						real_angle = 360 - walk_angle;
					}
					trex_direction = "sol alt";
				}
			}
			else // trex saðda
			{
				if((player_rect.y + 50) >= (trex_rect.y + 25)) // sað-üst
				{
					x_dis = abs((player_rect.x+50) - (trex_rect.x + 100));
					y_dis = abs((player_rect.y+50) - (trex_rect.y + 25));

					if(x_dis == 0)
					{
						walk_angle = 0;
						real_angle = 90;
					}
					if(y_dis == 0)
					{
						walk_angle = 0;
						real_angle = 180;
					}
					else
					{
						trex_tanjant = y_dis / x_dis;
						walk_angle = (atan(trex_tanjant) * 180) / PI ;
						real_angle = 180 - walk_angle;
					}
					trex_direction = "sag ust";
				}
				else // sað-alt
				{
					x_dis = abs((player_rect.x+50) - (trex_rect.x + 100));
					y_dis = abs((player_rect.y+50) - (trex_rect.y + 25));
					
					if(x_dis == 0)
					{
						walk_angle = 0;
						real_angle = 270;
					}
					else if(y_dis == 0)
					{
						walk_angle = 0;
						real_angle = 180;
					}
					else
					{
						trex_tanjant = y_dis / x_dis;
						walk_angle = (atan(trex_tanjant) * 180) / PI ;
						real_angle = 180 + walk_angle ;
					}
					trex_direction = "sag alt";
				}
			}
			
			///// TREX KOORDÝNAT /////
			if((!SDL_HasIntersection(&trex_rect , &player_rect)))
			{
				trex_speed = 10;
				if(trex_walk_time == 0)
					trex_walk_time = real_time + trex_walk_delay_time ;

				if(real_time >= trex_walk_time)
				{
					if(trex_direction == "sag alt") // sað-alt
					{	
						trex_x = trex_x - (int)(trex_speed*cos(((walk_angle)*PI)/180));
						trex_y = trex_y - (int)(trex_speed*sin(((walk_angle)*PI)/180));
						trex_walk_time = 0;
					}
					else if(trex_direction == "sol alt") // sol-alt
					{
						trex_x = trex_x + (int)(trex_speed*cos(((walk_angle)*PI)/180));
						trex_y = trex_y - (int)(trex_speed*sin(((walk_angle)*PI)/180));
						trex_walk_time = 0;
					}
					else if(trex_direction == "sol ust") // sol-üst
					{
						trex_x = trex_x + (int)(trex_speed*cos(((walk_angle)*PI)/180));
						trex_y = trex_y + (int)(trex_speed*sin(((walk_angle)*PI)/180));
						trex_walk_time = 0;
					}
					else if(trex_direction == "sag ust") // sað-üst
					{	
						trex_x = trex_x - (int)(trex_speed*cos(((walk_angle)*PI)/180));
						trex_y = trex_y + (int)(trex_speed*sin(((walk_angle)*PI)/180));
						trex_walk_time = 0;
					}
					
				}
				
			}
			else
			{
				trex_speed = 0;
				if(!Mix_Playing(3))
				{
					Mix_PlayChannel(3 , trex_roar , 0);
				}
			}
			
			trex_rect.x = (trex_x + camx);
			trex_rect.y = (trex_y + camy);

			SDL_RenderCopyEx(rend , enemy_map[trex_array[index_trex]] , NULL , &trex_rect , real_angle , 0 , SDL_FLIP_NONE);
		}

		else // bir sonraki resmi çiz
		{
			trex_rect.x = (trex_x + camx);
			trex_rect.y = (trex_y + camy);

			trex_current_time = real_time + trex_delay_time;
			index_trex++;

			if(index_trex == 4)
			{
				index_trex = 0;
			}

			SDL_RenderCopyEx(rend , enemy_map[trex_array[index_trex]] , NULL , &trex_rect , real_angle , 0 , SDL_FLIP_NONE);
		}

	}

	else if(trex_health <= 0.0) // eðer trex ölmüþse
	{
		trex_rect.x = (trex_x + camx);
		trex_rect.y = (trex_y + camy);
		
		if(trex_dead == true)
		{
			if(trex_dead_time == 0)
			{
				trex_dead_time = real_time + 10000 ;
				trex_rect.h = 100;
			}
			if(real_time <= trex_dead_time)
			{
				SDL_RenderCopyEx(rend , enemy_map[trex_array[4]] , NULL , &trex_rect , 0 , 0 , SDL_FLIP_NONE);
			}
			else
			{
				trex_dead_time = 0;
				trex_dead = false;
			}
		
		}
		
		else
		{
				trex_dead = false;

				trex_health = 300.0;

				real_angle = 0;
				walk_angle = 0;

				index_trex = 0;

				trex_x = -100;
				trex_y = rand() % 1200;

				trex_rect.h = 70;
			
		}
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

	load_enemy("assets/trex/trex1.png", "trex_a_1", renderer); // attack	indice = 0
	load_enemy("assets/trex/trex2.png", "trex_a_2", renderer); // attack	indice = 1
	load_enemy("assets/trex/trex3.png", "trex_a_3", renderer); // move		indice = 2
	load_enemy("assets/trex/trex4.png", "trex_a_4", renderer); // move		indice = 3
	load_enemy("assets/trex/trex_dead.png", "trex_a_5", renderer); // dead  indice = 4
	
}