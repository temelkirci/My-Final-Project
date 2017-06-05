#include <SDL/SDL.h>
#include <iostream>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <SDL/SDL_image.h>
#include "Game.h"

using namespace std;

Game::Game()
{
	pencere = NULL ;
	texture = NULL ;
	surface = NULL ;
	renderer = NULL ;
}

Game::~Game()
{
	SDL_DestroyWindow(pencere); // pencere yi serbest b�rak
	SDL_DestroyRenderer(renderer); // renderer i serbest b�rak
	SDL_FreeSurface(surface); // y�zeyi serbest b�rak
	SDL_DestroyTexture(texture); // texture yi serbest b�rak

	Mix_FreeMusic(tap);

	pencere = NULL ;
	texture = NULL ;
	surface = NULL ;
	renderer = NULL ;

	TTF_Quit(); // T�m yaz� sistemini kapat�r
	IMG_Quit(); // SDL_image.h i�eri�ini kapat�r
	Mix_Quit(); // "SDL_mixer.h" i�eri�ini kapat�r
	SDL_Quit();
}

bool Game :: init(const char* ba�l�k , int x , int y , int y�kseklik , int geni�lik , int bayraklar)
{
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0) // SDL hatas�z y�klenirse
		{
			pencere = SDL_CreateWindow(ba�l�k , x , y , y�kseklik , geni�lik , bayraklar); // Pencere olu�tur
			
			IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG); // Resimleri aktif et
			TTF_Init(); // Yazi fontlar�n� aktif et
			Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG); // Sesleri aktif et

			if(pencere == NULL )
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Pencere Olusturma Hatasi" , NULL);
				exit(0);
			}
			
			if(pencere != 0 ) // Pencere olu�ursa renderle
			{	
				renderer = SDL_CreateRenderer(pencere , -1 , SDL_RENDERER_ACCELERATED); // pencereyi renderle 
				
					// ARKAPLAN Y�KLEME BASLA
					SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 , 255);
					SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
					
					fonts_y�kle();
					cout<<"fontlar yuklendi"<<endl;
					load_inf(renderer);
					cout<<"load_inf yuklendi"<<endl;
					//MEN� Y�KLE
					load_buttonss(renderer);
					cout<<"butonlar yuklendi"<<endl;
					death_information(renderer);
					cout<<"olum penceresi yuklendi"<<endl;
					// M�Z�KLER� Y�KLE
					load_sounds(renderer);
					cout<<"sesler yuklendi"<<endl;
					//load_animation(renderer);
					enemy_load(renderer);
					cout<<"dusmanlar yuklendi"<<endl;
			}	
			else
			{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Render Hatasi" , NULL);
					exit(0);
			}			
			
		}
		else
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "SDL Baslatma Hatasi" , NULL);
			exit(0);
		}
			
	return true; 
}


