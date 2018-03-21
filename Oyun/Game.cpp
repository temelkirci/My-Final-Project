#include "Game.h"

Game::Game()
{
	mMainWindow = NULL;
	mRenderer = NULL;
}

Game::Game(const Game& pGame)
{

}

Game& Game::operator = (const Game& pGame)
{
	return *this;
}

Game::~Game()
{
	SDL_DestroyWindow(mMainWindow); // pencere yi serbest býrak
	SDL_DestroyRenderer(mRenderer); // renderer i serbest býrak

	mMainWindow = NULL;
	mRenderer = NULL;

	TTF_Quit(); // Tüm yazý sistemini kapatýr
	IMG_Quit(); // SDL_image.h içeriðini kapatýr
	Mix_Quit(); // "SDL_mixer.h" içeriðini kapatýr
	SDL_Quit();
}

bool Game::initializeGame(const char* pMenuTitle , int pX , int pY , int pHeight , int pLenght , int pFlags)
{
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0) // SDL hatasýz yüklenirse
		{
			mMainWindow = SDL_CreateWindow(pMenuTitle , pX , pY , pHeight , pLenght , pFlags); // Pencere oluþtur
				
			if(mMainWindow == NULL )
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Pencere Olusturma Hatasi" , NULL);
				return false;
			}

			IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG); // Resimleri aktif et
			TTF_Init(); // Yazi fontlarýný aktif et
			Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG); // Sesleri aktif et		
			
			if(mMainWindow != 0 ) // Pencere oluþursa renderle
			{	
				mRenderer = SDL_CreateRenderer(mMainWindow, -1 , SDL_RENDERER_ACCELERATED); // pencereyi renderle 
				
				// ARKAPLAN YÜKLEME BASLA
				SDL_SetRenderDrawColor(mRenderer, 0 , 0 , 0 , 255);
				SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

				GameState = GAME_STATE::OPENING;

				return true;
					
			}	
			else
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Render Hatasi" , NULL);
				return false;
			}			
			
		}
		else
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "SDL Baslatma Hatasi" , NULL);
			return false;
		}
			
	return true; 
}


void Game::startApplication()
{
	if (GameState == GAME_STATE::OPENING)
	{
		loadMenuFiles(mRenderer);

		GameState = GAME_STATE::MENU;

		while (GameState == GAME_STATE::MENU) // Draw the Menu
		{
			renderMenu(mRenderer);
			eventHandling();
		}
	}

	
	if (GameState == GAME_STATE::STARTING)
	{
		// bütün renderlenecek nesneleri yükle
		loadGameObjects(mRenderer);
		GameState = GAME_STATE::PLAYING;
	}
	
	while(GameState == GAME_STATE::PLAYING)
	{
		gameLoop(mRenderer); // Oyun döngüsüne baþla
		event(mRenderer); // olaylarý dinle
	}
	
}