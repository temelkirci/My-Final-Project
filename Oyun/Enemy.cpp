#include <iostream>
#include "SDL/SDL.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <SDL/SDL_image.h>
#include "SDL/SDL_mixer.h"

#define PI 3.14159265

Enemy :: Enemy()
{
	srand ((unsigned int)time(0));

	airplane_time = 0;
	creature_time = 0;
	creature_health = 100;

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3072) < 0 )
						cout<<"Mix_OpenAudio yüklenemedi "<<Mix_GetError()<<endl;

}

Enemy :: ~Enemy()
{

}

void Enemy :: load_enemy(char* file_path, char* enemy_picture , SDL_Renderer* render)
{
	SDL_Surface* surface_enemy = IMG_Load(file_path);
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

void Enemy :: drawAirplane(SDL_Renderer* render , int camerax , int cameray , Uint32 current_time)
{
	airplane_rect.x = 100 + camerax;
	airplane_rect.y = 100 + cameray;
	airplane_rect.w = 300;
	airplane_rect.h = 300;

	

		if(airplane_time == 0)
		{
			airplane_time = 300 + current_time;
		}
		
		if(current_time <= airplane_time) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["airplane1"] , NULL , &airplane_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((current_time > airplane_time) && (current_time <= (airplane_time + 300))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["airplane2"] , NULL , &airplane_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((current_time > (airplane_time + 300)) && (current_time <= (airplane_time + 600))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["airplane3"] , NULL , &airplane_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((current_time > (airplane_time + 600)) && (current_time <= (airplane_time + 900))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["airplane4"] , NULL , &airplane_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else
		{
			airplane_time = 0;
			SDL_RenderCopyEx(render , enemy_map["airplane1"] , NULL , &airplane_rect , 0 , 0 , SDL_FLIP_NONE);
		}	
}

void Enemy :: drawCreature(SDL_Renderer* render , int camerax , int cameray , Uint32 currentt_time)
{

	creature_rect.x = 1000 + camerax;
	creature_rect.y = 100 + cameray;
	creature_rect.w = 100;
	creature_rect.h = 100;

	cout<<currentt_time<<endl;
	
		if(creature_time == 0)
		{
			creature_time = 300 + currentt_time;
		}
		
		if(currentt_time <= creature_time) // 50 ms sayarsa
		{		
			SDL_RenderCopyEx(render , enemy_map["creature0"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);		
		}
		else if((currentt_time > creature_time) && (currentt_time <= (creature_time + 300))) // 50 ms sayarsa
		{
			SDL_RenderCopyEx(render , enemy_map["creature1"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 300)) && (currentt_time <= (creature_time + 600))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["creature2"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 600)) && (currentt_time <= (creature_time + 900))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["creature3"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > creature_time + 1200) && (currentt_time <= (creature_time + 1500))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["creature4"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 1800)) && (currentt_time <= (creature_time + 2100))) // 50 ms sayarsa
		{		
			SDL_RenderCopyEx(render , enemy_map["creature5"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 2400)) && (currentt_time <= (creature_time + 2700))) // 50 ms sayarsa
		{		
			SDL_RenderCopyEx(render , enemy_map["creature6"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > creature_time + 3000) && (currentt_time <= (creature_time + 3300))) // 50 ms sayarsa
		{		
			SDL_RenderCopyEx(render , enemy_map["creature7"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 3600)) && (currentt_time <= (creature_time + 3900))) // 50 ms sayarsa
		{		
			SDL_RenderCopyEx(render , enemy_map["creature8"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else if((currentt_time > (creature_time + 4200)) && (currentt_time <= (creature_time + 4500))) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(render , enemy_map["creature9"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}
		else
		{
			creature_time = 0;
			SDL_RenderCopyEx(render , enemy_map["creature0"] , NULL , &creature_rect , 0 , 0 , SDL_FLIP_NONE);
		}	
}

void Enemy :: enemy_load(SDL_Renderer* renderer)
{
	load_enemy("assets/enemies/airplane/1.png" , "airplane1" , renderer);
	load_enemy("assets/enemies/airplane/2.png" , "airplane2" , renderer);
	load_enemy("assets/enemies/airplane/3.png" , "airplane3" , renderer);
	load_enemy("assets/enemies/airplane/4.png" , "airplane4" , renderer);

	load_enemy("assets/enemies/creature/0.png" , "creature0" , renderer);
	load_enemy("assets/enemies/creature/1.png" , "creature1" , renderer);
	load_enemy("assets/enemies/creature/2.png" , "creature2" , renderer);
	load_enemy("assets/enemies/creature/3.png" , "creature3" , renderer);
	load_enemy("assets/enemies/creature/4.png" , "creature4" , renderer);
	load_enemy("assets/enemies/creature/5.png" , "creature5" , renderer);
	load_enemy("assets/enemies/creature/6.png" , "creature6" , renderer);
	load_enemy("assets/enemies/creature/7.png" , "creature7" , renderer);
	load_enemy("assets/enemies/creature/8.png" , "creature8" , renderer);
	load_enemy("assets/enemies/creature/9.png" , "creature9" , renderer);

	load_enemy("assets/mhouse.png" , "house" , renderer);
}
