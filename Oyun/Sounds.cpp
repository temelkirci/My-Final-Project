#include <iostream>
#include "Sounds.h"
#include "SDL/SDL.h"

using namespace std;

Sounds ::Sounds()
{
	
}

Sounds::~Sounds()
{

}

void Sounds :: load_sounds(SDL_Renderer* render)
{
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3072) < 0 )
						cout<<"Mix_OpenAudio yüklenemedi "<<Mix_GetError()<<endl;


	tap = Mix_LoadMUS("assets/sounds/menu.ogg"); // menü müziði
					
	Mix_VolumeMusic(100);	
	Mix_PlayMusic(tap, -1 );
					
	minigun_shot = Mix_LoadWAV("assets/sounds/GunShot2.wav");
	shotgun_shot = Mix_LoadWAV("assets/sounds/shotgun.wav");
	rifle_shot = Mix_LoadWAV("assets/sounds/rifle.wav");
	walk = Mix_LoadWAV("assets/sounds/walk.wav");
	food = Mix_LoadWAV("assets/sounds/food.wav");
	water_drink = Mix_LoadWAV("assets/sounds/drinking.wav");
}
