#pragma once
#include <iostream>
#include <string>
#include "SDL/SDL_mixer.h"
#include <map>
#include "SDL/SDL.h"
#include "Items.h"

using namespace std;

class Sounds : public Items
{
public:

	Sounds();
	~Sounds();

	Mix_Music *tap;
	Mix_Chunk *walk;
	Mix_Chunk *minigun_shot;
	Mix_Chunk *shotgun_shot;
	Mix_Chunk *rifle_shot;

	void load_sounds(SDL_Renderer*);
private:
	
};