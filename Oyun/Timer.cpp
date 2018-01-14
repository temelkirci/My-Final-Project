#include "SDL/SDL.h"
#include <iostream>
#include "Timer.h"
#include "SDL/SDL_ttf.h"
#include <chrono>

using namespace std;

Timer :: Timer()
{
	timer_textColor.r = 0;
	timer_textColor.g = 0;
	timer_textColor.b = 0;
	timer_textColor.a = 255;

	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 255;

	world.x = 0;
	world.y = 0;
	world.w = 6000;
	world.h = 3000;

	toplam_time = 0;
	real_time = 0;
	day = 1;
	gecen_s�re = 0;
	oldTime = 0;
	active = true;
	night = false; // oyun g�nd�z olarak ba�layacak
	saat = 12; // oyun ��len 12 de ba�layacak

	startTime = false;
}

Timer :: ~Timer()
{

}

Uint32 Timer :: s�re_hesapla(Uint32 ilks�re , Uint32 sons�re)
{	
	return (sons�re-ilks�re)/1000; 	
}

void Timer :: calculateTime(int time) // saniye
{

	if(!startTime)
	{
		start = std::chrono::steady_clock::now();
		startTime = true;
	}

	chrono::steady_clock::time_point   end = std::chrono::steady_clock::now();
	chrono::steady_clock::duration   elapsed = end - start;

	                                                                         
	if(chrono::duration_cast<chrono::milliseconds>(elapsed).count() / 1000.0 >= time)
	{
		cout<<time<<" saniye gecti "<<endl;
	}
	else
	{
		cout<<"Time : "<<chrono::duration_cast<chrono::milliseconds>(elapsed).count() / 1000.0 <<endl;
		
	}
	
}

void Timer :: gece_g�nd�z(SDL_Renderer* rend , Uint32 gercek_zaman)
{
	
	if(toplam_time == 0)
	{
		toplam_time = gercek_zaman + 100;
	}

	if((gercek_zaman <= toplam_time)) // gece g�nd�z d�ng�s� 1 sn
	{
		SDL_SetRenderDrawColor(rend , 0 , 0 , 0 , real_time); //
		SDL_RenderFillRect(rend, &world);
	}
	else // 1 sn ge�tikten sonra
	{
		toplam_time = 0;
		if((real_time < 240) && !night)
		{
			real_time = real_time + 1;
			saat = real_time/20 + 12;
			if(saat == 24)
				saat = 0;
			SDL_SetRenderDrawColor(rend , 0 , 0 , 0 , real_time); //
			SDL_RenderFillRect(rend, &world);
		}
		else if((real_time >= 240) && !night)
		{
			night = true;
			saat = 0;
			SDL_SetRenderDrawColor(rend , 0 , 0 , 0 , real_time); //
			SDL_RenderFillRect(rend, &world);
		}
		else if(night)
		{
			real_time = real_time - 1;
			saat = 12 - real_time/20;
			if(saat == 24)
				saat = 0;
			SDL_SetRenderDrawColor(rend , 0 , 0 , 0 , real_time); //
			SDL_RenderFillRect(rend, &world);
			if(real_time == 0)
			{
				saat = 12;
				night = false;
				day++;
			}
		}
	}
	
}

void Timer :: Write(SDL_Renderer* rend , Uint32 zaman , string text , Uint32 delay_time)
{
	if(zaman != 0)
	{
		if(active)
		{
			if((gecen_s�re == 0)) // ilk zaman� sakla
			{
				if(delay_time == -1)
					gecen_s�re = zaman + 1000;
				else
					gecen_s�re = zaman + delay_time; // yaz� ekranda delay_time kadar g�r�necek
			}
	
			if((delay_time < gecen_s�re)) // yaz�n�n ekranda g�z�kme s�resi
			{
		
			SDL_Rect yazi;
				yazi.x = 250 + (425 - (text.length()*10)/2);
				yazi.y = 5;
				yazi.w = text.length()*10;
				yazi.h = 25;

				SDL_Surface* temel = TTF_RenderText_Blended( timer_font , text.c_str() , textColor );
				yazii_texture = SDL_CreateTextureFromSurface(rend, temel );
				SDL_FreeSurface(temel);

				SDL_RenderCopyEx(rend , yazii_texture , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
				SDL_DestroyTexture(yazii_texture);
				
			}
			else
			{
				if(delay_time == -1)
				{
					gecen_s�re = zaman + 1000;
					active = true;
				}
				else
				{
					gecen_s�re = 0;	
					active = false;
				}
			}
		}
	}
	else
	{
		
		SDL_Rect yazii;
		yazii.x = 250 + (425 - (text.length()*10)/2);
		yazii.y = 0;
		yazii.w = text.length()*10;
		yazii.h = 25;
				
		SDL_Surface* temell = TTF_RenderText_Blended( timer_font , text.c_str() , timer_textColor );
		yazii_texture = SDL_CreateTextureFromSurface(rend, temell );
		SDL_FreeSurface(temell);

		SDL_RenderCopyEx(rend , yazii_texture , NULL , &yazii , 0 , 0 , SDL_FLIP_NONE);
		SDL_DestroyTexture(yazii_texture);
	}
}

void Timer :: loadFonts()
{
	timer_font = TTF_OpenFont("fonts/fontss.ttf", 140);
}