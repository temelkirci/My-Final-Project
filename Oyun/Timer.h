#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <chrono>
#include <string>

using namespace std::chrono;
using namespace std;

class Timer
{
public:
	Timer();
	Timer(const Timer& pTimer);
	Timer& operator = (const Timer& pTimer);
	~Timer();
	
	void writeText(SDL_Renderer* pRenderer , Uint32 pTime , string pText, Uint32 pDelayTime);
	void loadFonts();
	void dayLoop(SDL_Renderer* pRenderer, Uint32 pCurrentTime);
	bool calculateTime(int pTime);

	int getDay();
	int getHour();

private:

	Uint32 mElaspedTime;
	int mDay;
	Uint32 mCurrentTime;
	bool mNight;
	Uint32 mTotalTime;
	SDL_Texture* mTextTexture;
	TTF_Font* mTimerFont;
	SDL_Color mTimerTextColor;
	SDL_Color mTextColor;
	bool mTextActive;
	SDL_Rect mWorldRect;
	int mHour;
	bool mStartTime;
	steady_clock::time_point mStartTimePoint;
};