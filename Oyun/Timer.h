#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Enemy.h"

class Timer : public Enemy
{
public:
	Timer();
	~Timer();

	Uint32 süre_hesapla(Uint32,Uint32);
	void Write(SDL_Renderer*  , Uint32 , string);
	void fonts_yükle();
	void gece_gündüz(SDL_Renderer* , Uint32);
	int day;
	Uint8 real_time;
	bool night;
	Uint32 toplam_time;
	Uint32 first_time;
	Uint32 current_time;
	Uint32 oldTime;
	SDL_Texture* yazii_texture;
	TTF_Font* timer_font;
	SDL_Color timer_textColor;
	bool active;
	SDL_Texture* texture_background;
	SDL_Rect world;
	int saat;
private:
	Uint32 gecen_süre;
	
};