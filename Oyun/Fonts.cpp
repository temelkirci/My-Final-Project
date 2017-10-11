#include "Fonts.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>

Fonts :: Fonts()
{
	toplam = 0;

	backColor.r = 0;
	backColor.g = 0;
	backColor.b = 255;
	backColor.a = 150;

	backRect.x = 0;
	backRect.y = 0;
	backRect.w = 100;
	backRect.h = 30;

	arkaPlan.x = 0;
	arkaPlan.y = 0;
	arkaPlan.w = 180;
	arkaPlan.h = 160;

	dizi[0] = "health";
	dizi[1] = "hunger";
	dizi[2] = "thirsty";
	dizi[3] = "bullet";
	
}

Fonts :: ~Fonts()
{
	TTF_CloseFont(Font); // Yazi fontunu kapatýr
}

int Fonts :: Resim(char* resim_dosya, string resim_adi, SDL_Renderer* render)
{
	SDL_Surface * resim_surface = IMG_Load(resim_dosya);
	if(resim_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Fonts" , "Sol üst resimler yuklenemedi..!" , NULL);
		exit(0);
	}
	resim_texture = SDL_CreateTextureFromSurface(render , resim_surface);
	SDL_FreeSurface(resim_surface);

	if(resim_texture != 0)
	{
		resim_map[resim_adi] = resim_texture; 
		return true;
	}
	return false;

}

void Fonts :: barbaros_status(SDL_Renderer* render_font ,
							 int hx , int hy , 
							 int genislik , int yukseklik ,
							 int saglik , int mermi , int aclik , int susuzluk)

{
		healthRect.w = saglik; // source rect
		hungerRect.w = aclik;
		thirstyRect.w = susuzluk;

	//SDL_SetRenderDrawColor(render_font , 220 , 220 , 220 , 200); // gri arkaplan
	//SDL_RenderFillRect(render_font, &arkaPlan);
	
	for(int i=0; i<4 ; i++)
	{
		SDL_Rect yazi;
		yazi.x=hx;
		yazi.y=hy;
		yazi.w=genislik;
		yazi.h=yukseklik;

		SDL_RenderCopyEx(render_font , resim_map[dizi[i]] , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE); // saðlik resm , susuzluk resmi , açlýk resmi , mermi resmi
				
		// Saglýk , Mermi , Açlýk ve Susuzluk deðerleri
		backRect.x = hx+genislik+10;
		backRect.y = hy;
		backRect.w = 100;
		backRect.h = yukseklik;

		if(dizi[i] == "health")
		{
			SDL_SetRenderDrawColor(render_font , 47 , 79 , 79 , 150); // gri arkaplan
		    SDL_RenderFillRect(render_font, &backRect);

			healthRect.x = hx+genislik+10;
			healthRect.y = hy;
			healthRect.w = saglik;
			healthRect.h = yukseklik;

			SDL_SetRenderDrawColor(render_font , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(render_font, &healthRect);

		}
		else if(dizi[i] == "hunger")
		{
			SDL_SetRenderDrawColor(render_font , 47 , 79 , 79 , 150); // gri arkaplan
			SDL_RenderFillRect(render_font, &backRect);

			hungerRect.x = hx+genislik+10;
			hungerRect.y = hy;
			hungerRect.w = aclik;
			hungerRect.h = yukseklik;

			SDL_SetRenderDrawColor(render_font , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(render_font, &hungerRect);
		}
		else if(dizi[i] == "thirsty")
		{
			SDL_SetRenderDrawColor(render_font , 47 , 79 , 79 , 150); // gri arkaplan
			SDL_RenderFillRect(render_font, &backRect);

			thirstyRect.x = hx+genislik+10;
			thirstyRect.y = hy;
			thirstyRect.w = susuzluk;
			thirstyRect.h = yukseklik;

			SDL_SetRenderDrawColor(render_font , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(render_font, &thirstyRect);
		}

		else if(dizi[i] == "bullet")
		{
			SDL_Rect yazi;
			yazi.x=hx+genislik+10;;
			yazi.y=hy;
			yazi.w=genislik;
			yazi.h=yukseklik;
			
			string textt = to_string(mermi);
			
			SDL_Surface* textSurface = TTF_RenderText_Blended(Font , textt.c_str(), backColor );
			SDL_Texture* back_ground = SDL_CreateTextureFromSurface( render_font, textSurface );
			SDL_FreeSurface(textSurface);

			SDL_RenderCopyEx(render_font , back_ground , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(back_ground);
		}
		hy=hy+yukseklik+20;
	}
}


void Fonts :: Write_Text(SDL_Renderer* rend , Uint32 zaman , char* text)
{
	if(zaman != 0)
	{
		if(toplam == 0) // ilk zamaný sakla
			toplam = zaman + 3000;
	
		// yazý ekranda 3 sn görünecek
		if(total <= toplam) // yazýnýn ekranda gözükme süresi
		{
		
			SDL_Rect yazi;
			yazi.x=250;
			yazi.y=0;
			yazi.w=strlen(text)*25;
			yazi.h=30;

			SDL_Surface* textSurface = TTF_RenderText_Blended( Font , text, backColor );
			SDL_Texture* back_ground = SDL_CreateTextureFromSurface( rend, textSurface );
			SDL_FreeSurface(textSurface);

			SDL_RenderCopyEx(rend , back_ground , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(back_ground);
	
		}
		else
		{
			toplam = 0;
			// nothing
		}
	}
	else
	{
		SDL_Rect yazi;
			yazi.x=550;
			yazi.y=0;
			yazi.w=100;
			yazi.h=30;
			
			SDL_Surface* texttSurface = TTF_RenderText_Blended( Font , text , backColor );
			SDL_Texture* backk_ground = SDL_CreateTextureFromSurface( rend, texttSurface );
			SDL_FreeSurface(texttSurface);

			SDL_RenderCopyEx(rend , backk_ground , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(backk_ground);
	}
}

void Fonts :: load_Resim(SDL_Renderer* renderer)
{
	Font = TTF_OpenFont("fonts/Roboto-Regular.ttf", 100);
	
	Resim("assets/hunger.png", "hunger" , renderer); // açlýk icon'u
	Resim("assets/bullet.png", "bullet" , renderer); // mermi icon'u
	Resim("assets/health.png", "health" , renderer); // saðlýk icon'u
	Resim("assets/drop.png", "thirsty" , renderer); // susuzluk icon'u
}