#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Enemy.h"
#include <chrono>

class Timer : public Enemy
{
public:
	Timer();
	~Timer();
	SDL_Rect tank_rect;
	bool emel;
	Uint32 süre_hesapla(Uint32,Uint32);
	void Write(SDL_Renderer*  , Uint32 , string , Uint32);
	void loadFonts();
	void gece_gündüz(SDL_Renderer* , Uint32);
	void calculateTime(int);
	int day;
	Uint8 real_time;
	bool night;
	Uint32 toplam_time;
	Uint32 first_time;
	Uint32 oldTime;
	SDL_Texture* yazii_texture;
	TTF_Font* timer_font;
	SDL_Color timer_textColor;
	SDL_Color textColor;
	bool active;
	SDL_Texture* texture_background;
	SDL_Rect world;
	int saat;
	bool startTime;
	std::chrono::steady_clock::time_point start;
private:
	Uint32 gecen_süre;
	
};