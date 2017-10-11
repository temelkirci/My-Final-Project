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
	SDL_DestroyWindow(pencere); // pencere yi serbest býrak
	SDL_DestroyRenderer(renderer); // renderer i serbest býrak
	SDL_FreeSurface(surface); // yüzeyi serbest býrak
	SDL_DestroyTexture(texture); // texture yi serbest býrak

	Mix_FreeMusic(tap);

	pencere = NULL ;
	texture = NULL ;
	surface = NULL ;
	renderer = NULL ;

	TTF_Quit(); // Tüm yazý sistemini kapatýr
	IMG_Quit(); // SDL_image.h içeriðini kapatýr
	Mix_Quit(); // "SDL_mixer.h" içeriðini kapatýr
	SDL_Quit();
}

bool Game :: init(const char* baþlýk , int x , int y , int yükseklik , int geniþlik , int bayraklar)
{
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0) // SDL hatasýz yüklenirse
		{
			pencere = SDL_CreateWindow(baþlýk , x , y , yükseklik , geniþlik , bayraklar); // Pencere oluþtur
			win = pencere;
			
			glContext = SDL_GL_CreateContext(pencere);
				
			if(pencere == NULL )
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Pencere Olusturma Hatasi" , NULL);
				exit(0);
			}

			IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG); // Resimleri aktif et
			TTF_Init(); // Yazi fontlarýný aktif et
			Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG); // Sesleri aktif et		
			
			if(pencere != 0 ) // Pencere oluþursa renderle
			{	
				renderer = SDL_CreateRenderer(pencere , -1 , SDL_RENDERER_ACCELERATED); // pencereyi renderle 
				
					// ARKAPLAN YÜKLEME BASLA
					SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 , 255);
					SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
					
					
					loadFonts();
					loadInventory(renderer);
					load_inf(renderer);
					
					//MENÜ YÜKLE
					loadMenu(renderer);
					
					death_information(renderer);
					
					// MÜZÝKLERÝ YÜKLE
					loadSounds(renderer);
					
					//load_animation(renderer);
					enemy_load(renderer);
					
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


