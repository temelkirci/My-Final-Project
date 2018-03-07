#include "Sounds.h"

using namespace std;

Sounds ::Sounds()
{
	
}

Sounds::Sounds(const Sounds& pSounds)
{

}

Sounds& Sounds::operator = (const Sounds& pSounds)
{
	return *this;
}

Sounds::~Sounds()
{

}

Sounds* Sounds::getInstanceSounds()
{
	if (mInstanceSounds == 0)
		mInstanceSounds = new Sounds();

	return mInstanceSounds;
}

void Sounds :: loadSounds(SDL_Renderer* render)
{
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3072) < 0 )
						cout<<"Mix_OpenAudio yüklenemedi "<<Mix_GetError()<<endl;


	mMenuMusic = Mix_LoadMUS("assets/sounds/menu.ogg"); // menü müziği
					
	Mix_VolumeMusic(100);	
	Mix_PlayMusic(mMenuMusic, -1 );
					
	mHandgunShotSound = Mix_LoadWAV("assets/sounds/GunShot2.wav");
	mShotgunShotSound = Mix_LoadWAV("assets/sounds/shotgun.wav");
	mRifleShotSound = Mix_LoadWAV("assets/sounds/rifle.wav");
	mWalkSound = Mix_LoadWAV("assets/sounds/walk.wav");
	mFoodSound = Mix_LoadWAV("assets/sounds/food.wav");
	mWaterSound = Mix_LoadWAV("assets/sounds/drinking.wav");
}
