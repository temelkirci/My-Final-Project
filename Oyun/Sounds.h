#pragma once

#include <string>
#include "SDL/SDL_mixer.h"
#include <map>
#include "SDL/SDL.h"
#include <iostream>

using namespace std;

class Sounds 
{
public:

	Sounds();
	Sounds(const Sounds& pSounds);
	Sounds& operator = (const Sounds& pSounds);
	~Sounds();

	void loadSounds();

protected:

	Mix_Music* mMenuMusic;
	Mix_Chunk* mWalkSound;
	Mix_Chunk* mHandgunShotSound;
	Mix_Chunk* mShotgunShotSound;
	Mix_Chunk* mRifleShotSound;
	Mix_Chunk* mWaterSound;
	Mix_Chunk* mSoupSound;
	Mix_Chunk* mFoodSound;
};