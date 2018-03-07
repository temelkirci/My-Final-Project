#include "Enemy.h"

#define PI 3.14159265

Enemy :: Enemy()
{
	srand ((unsigned int)time(0));

	mAirplaneTime = 0;
	mCreatureTime = 0;
	mCreatureHealth = 100;
	mMoveTime = 0;

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3072) < 0 )
						cout<<"Mix_OpenAudio yüklenemedi "<<Mix_GetError()<<endl;

}

Enemy :: ~Enemy()
{

}

Enemy::Enemy(const Enemy& pEnemy)
{

}

Enemy& Enemy::operator = (const Enemy& pEnemy)
{
	return *this;
}

Enemy* Enemy::getInstanceEnemy()
{
	if (mInstanceEnemy == 0)
		mInstanceEnemy = new Enemy();

	return mInstanceEnemy;
}

void Enemy :: loadEnemyItems(char* pPathFile, char* pEnemyImage , SDL_Renderer* pRenderer)
{
	SDL_Surface* tEnemySurface = IMG_Load(pPathFile);
	if(tEnemySurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Enemy" , "Enemy yuklenemedi..!" , NULL);
		exit(0);
	}

	SDL_Texture* tEnemyTexture = SDL_CreateTextureFromSurface(pRenderer, tEnemySurface);
	SDL_FreeSurface(tEnemySurface);

	if(tEnemyTexture != 0)
	{
		mEnemyMap[pEnemyImage] = tEnemyTexture;
	}
}

void Enemy :: drawAirplane(SDL_Renderer* pRender , int pCamerax , int pCameray , Uint32 pCurrentTime)
{
	mAirplaneRect.x = 100 + pCamerax;
	mAirplaneRect.y = 100 + pCameray;
	mAirplaneRect.w = 300;
	mAirplaneRect.h = 300;

	

		if(mAirplaneTime == 0)
		{
			mAirplaneTime = 300 + pCurrentTime;
		}
		
		if(pCurrentTime <= mAirplaneTime) // 50 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["airplane1"] , NULL , &mAirplaneRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > mAirplaneTime) && (pCurrentTime <= (mAirplaneTime + 300))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["airplane2"] , NULL , &mAirplaneRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mAirplaneTime + 300)) && (pCurrentTime <= (mAirplaneTime + 600))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["airplane3"] , NULL , &mAirplaneRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mAirplaneTime + 600)) && (pCurrentTime <= (mAirplaneTime + 900))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["airplane4"] , NULL , &mAirplaneRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else
		{
			mAirplaneTime = 0;
			SDL_RenderCopyEx(pRender, mEnemyMap["airplane1"] , NULL , &mAirplaneRect, 0 , 0 , SDL_FLIP_NONE);
		}	
}

void Enemy :: drawCreature(SDL_Renderer* pRender , int pCamerax , int pCameray , SDL_Rect pPlayerRect , Uint32 pCurrentTime)
{
	mCreatureRect.x = 1000 + pCamerax;
	mCreatureRect.y = 100 + pCameray;
	mCreatureRect.w = 100;
	mCreatureRect.h = 100;

		if(mCreatureTime == 0)
		{
			mCreatureTime = 300 + pCurrentTime;
		}
		
		if(pCurrentTime <= mCreatureTime) // 300 ms sayarsa
		{		
			SDL_RenderCopyEx(pRender, mEnemyMap["creature0"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}

		else if((pCurrentTime > mCreatureTime) && (pCurrentTime <= (mCreatureTime + 300))) // 300 ms sayarsa
		{
			SDL_RenderCopyEx(pRender, mEnemyMap["creature1"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 300)) && (pCurrentTime <= (mCreatureTime + 600))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["creature2"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 600)) && (pCurrentTime <= (mCreatureTime + 900))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["creature3"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > mCreatureTime + 1200) && (pCurrentTime <= (mCreatureTime + 1500))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["creature4"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 1800)) && (pCurrentTime <= (mCreatureTime + 2100))) // 300 ms sayarsa
		{		
			SDL_RenderCopyEx(pRender, mEnemyMap["creature5"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 2400)) && (pCurrentTime <= (mCreatureTime + 2700))) // 300 ms sayarsa
		{		
			SDL_RenderCopyEx(pRender, mEnemyMap["creature6"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > mCreatureTime + 3000) && (pCurrentTime <= (mCreatureTime + 3300))) // 300 ms sayarsa
		{		
			SDL_RenderCopyEx(pRender, mEnemyMap["creature7"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 3600)) && (pCurrentTime <= (mCreatureTime + 3900))) // 300 ms sayarsa
		{		
			SDL_RenderCopyEx(pRender, mEnemyMap["creature8"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else if((pCurrentTime > (mCreatureTime + 4200)) && (pCurrentTime <= (mCreatureTime + 4500))) // 300 ms sayarsa
		{			
			SDL_RenderCopyEx(pRender, mEnemyMap["creature9"] , NULL , &mCreatureRect, 0 , 0 , SDL_FLIP_NONE);
		}
		else
		{
			mCreatureTime = 0;
			SDL_RenderCopyEx(pRender, mEnemyMap["creature0"] , NULL , &mCreatureRect , 0 , 0 , SDL_FLIP_NONE);
		}	
}

void Enemy :: loadEnemy(SDL_Renderer* pRenderer)
{
	loadEnemyItems("assets/enemies/airplane/1.png" , "airplane1" , pRenderer);
	loadEnemyItems("assets/enemies/airplane/2.png" , "airplane2" , pRenderer);
	loadEnemyItems("assets/enemies/airplane/3.png" , "airplane3" , pRenderer);
	loadEnemyItems("assets/enemies/airplane/4.png" , "airplane4" , pRenderer);

	loadEnemyItems("assets/enemies/creature/0.png" , "creature0" , pRenderer);
	loadEnemyItems("assets/enemies/creature/1.png" , "creature1" , pRenderer);
	loadEnemyItems("assets/enemies/creature/2.png" , "creature2" , pRenderer);
	loadEnemyItems("assets/enemies/creature/3.png" , "creature3" , pRenderer);
	loadEnemyItems("assets/enemies/creature/4.png" , "creature4" , pRenderer);
	loadEnemyItems("assets/enemies/creature/5.png" , "creature5" , pRenderer);
	loadEnemyItems("assets/enemies/creature/6.png" , "creature6" , pRenderer);
	loadEnemyItems("assets/enemies/creature/7.png" , "creature7" , pRenderer);
	loadEnemyItems("assets/enemies/creature/8.png" , "creature8" , pRenderer);
	loadEnemyItems("assets/enemies/creature/9.png" , "creature9" , pRenderer);
}
