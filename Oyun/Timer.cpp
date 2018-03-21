#include "Timer.h"

using namespace std;
using namespace std::chrono;

Timer :: Timer()
{
	mTimerTextColor.r = 0;
	mTimerTextColor.g = 0;
	mTimerTextColor.b = 0;
	mTimerTextColor.a = 255;

	mTextColor.r = 0;
	mTextColor.g = 0;
	mTextColor.b = 0;
	mTextColor.a = 255;

	mWorldRect.x = 0;
	mWorldRect.y = 0;
	mWorldRect.w = 6000;
	mWorldRect.h = 3000;

	mTotalTime = 0;
	mCurrentTime = 0;
	mDay = 1;
	mElaspedTime = 0;

	mTextActive = true;
	mNight = false; // oyun gündüz olarak baþlayacak
	mHour = 12; // oyun öðlen 12 de baþlayacak

	mStartTime = false;
}

Timer::Timer(const Timer& pTimer)
{

}

Timer& Timer::operator = (const Timer& pTimer)
{
	return *this;
}

Timer :: ~Timer()
{

}

bool Timer::calculateTime(int pTime) // saniye
{

	if(!mStartTime)
	{
		mStartTimePoint = steady_clock::now();
		mStartTime = true;
	}

	steady_clock::time_point tEndTimePoint = steady_clock::now();
	steady_clock::duration tElapsedTimePoint = tEndTimePoint - mStartTimePoint;

	if(duration_cast<milliseconds>(tElapsedTimePoint).count() / 1000.0 >= pTime) // istenilen zaman ölçüldüyse
	{
		mStartTime = false;
		return true;
	}
	else
	{
		return false;
	}	
}

void Timer :: dayLoop(SDL_Renderer* pRenderer , Uint32 pCurrentTime)
{
	if(mTotalTime == 0)
	{
		mTotalTime = pCurrentTime + 100;
	}

	if((pCurrentTime <= mTotalTime)) // gece gündüz döngüsü 1 sn
	{
		SDL_SetRenderDrawColor(pRenderer , 0 , 0 , 0 , pCurrentTime); //
		SDL_RenderFillRect(pRenderer, &mWorldRect);
	}
	else // 1 sn geçtikten sonra
	{
		mTotalTime = 0;
		if((pCurrentTime < 240) && !mNight)
		{
			mCurrentTime = mCurrentTime + 1;
			mHour = mCurrentTime /20 + 12;
			if(mHour == 24)
				mHour = 0;
			SDL_SetRenderDrawColor(pRenderer, 0 , 0 , 0 , mCurrentTime); //
			SDL_RenderFillRect(pRenderer, &mWorldRect);
		}
		else if((pCurrentTime >= 240) && !mNight)
		{
			mNight = true;
			mHour = 0;
			SDL_SetRenderDrawColor(pRenderer, 0 , 0 , 0 , mCurrentTime); //
			SDL_RenderFillRect(pRenderer, &mWorldRect);
		}
		else if(mNight)
		{
			mCurrentTime = mCurrentTime - 1;
			mHour = 12 - mCurrentTime /20;
			if(mHour == 24)
				mHour = 0;
			SDL_SetRenderDrawColor(pRenderer, 0 , 0 , 0 , mCurrentTime); //
			SDL_RenderFillRect(pRenderer, &mWorldRect);
			if(pCurrentTime == 0)
			{
				mHour = 12;
				mNight = false;
				mDay++;
			}
		}
	}
	
}

int Timer::getDay()
{
	return mDay;
}

int Timer::getHour()
{
	return mHour;
}

void Timer :: writeText(SDL_Renderer* pRenderer, Uint32 pTime , string pText , Uint32 pDelayTime)
{
	if(pTime != 0)
	{
		if(mTextActive)
		{
			if((mElaspedTime == 0)) // ilk zamaný sakla
			{
				if(pDelayTime == -1)
					mElaspedTime = pTime + 1000;
				else
					mElaspedTime = pTime + pDelayTime; // yazý ekranda delay_time kadar görünecek
			}
	
			if((pDelayTime < mElaspedTime)) // yazýnýn ekranda gözükme süresi
			{
		
			SDL_Rect tText;
				tText.x = 250 + (425 - (pText.length()*10)/2);
				tText.y = 5;
				tText.w = pText.length()*10;
				tText.h = 25;

				SDL_Surface* tTextSurface = TTF_RenderText_Blended( mTimerFont , pText.c_str() , mTextColor );
				mTextTexture = SDL_CreateTextureFromSurface(pRenderer, tTextSurface);
				SDL_FreeSurface(tTextSurface);

				SDL_RenderCopyEx(pRenderer, mTextTexture, NULL , &tText, 0 , 0 , SDL_FLIP_NONE);
				SDL_DestroyTexture(mTextTexture);
				
			}
			else
			{
				if(pDelayTime == -1)
				{
					mElaspedTime = pTime + 1000;
					mTextActive = true;
				}
				else
				{
					mElaspedTime = 0;
					mTextActive = false;
				}
			}
		}
	}
	else
	{
		
		SDL_Rect tText;
		tText.x = 250 + (425 - (pText.length()*10)/2);
		tText.y = 0;
		tText.w = pText.length()*10;
		tText.h = 25;
				
		SDL_Surface* tSurfaceText = TTF_RenderText_Blended( mTimerFont , pText.c_str() , mTimerTextColor );
		mTextTexture = SDL_CreateTextureFromSurface(pRenderer, tSurfaceText);
		SDL_FreeSurface(tSurfaceText);

		SDL_RenderCopyEx(pRenderer, mTextTexture, NULL , &tText, 0 , 0 , SDL_FLIP_NONE);
		SDL_DestroyTexture(mTextTexture);
	}
}

void Timer :: loadFonts()
{
	mTimerFont = TTF_OpenFont("fonts/fontss.ttf", 140);
}