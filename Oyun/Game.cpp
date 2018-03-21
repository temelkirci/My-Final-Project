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
	SDL_DestroyWindow(mMainWindow); // pencere yi serbest b�rak
	SDL_DestroyRenderer(mRenderer); // renderer i serbest b�rak

	mMainWindow = NULL;
	mRenderer = NULL;

	TTF_Quit(); // T�m yaz� sistemini kapat�r
	IMG_Quit(); // SDL_image.h i�eri�ini kapat�r
	Mix_Quit(); // "SDL_mixer.h" i�eri�ini kapat�r
	SDL_Quit();
}

bool Game::initializeGame(const char* pMenuTitle , int pX , int pY , int pHeight , int pLenght , int pFlags)
{
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0) // SDL hatas�z y�klenirse
		{
			mMainWindow = SDL_CreateWindow(pMenuTitle , pX , pY , pHeight , pLenght , pFlags); // Pencere olu�tur
				
			if(mMainWindow == NULL )
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "Pencere Olusturma Hatasi" , NULL);
				return false;
			}

			IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG); // Resimleri aktif et
			TTF_Init(); // Yazi fontlar�n� aktif et
			Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG); // Sesleri aktif et		
			
			if(mMainWindow != 0 ) // Pencere olu�ursa renderle
			{	
				mRenderer = SDL_CreateRenderer(mMainWindow, -1 , SDL_RENDERER_ACCELERATED); // pencereyi renderle 
				
				// ARKAPLAN Y�KLEME BASLA
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
		// b�t�n renderlenecek nesneleri y�kle
		loadGameObjects(mRenderer);
		GameState = GAME_STATE::PLAYING;
	}
	
	while(GameState == GAME_STATE::PLAYING)
	{
		gameLoop(mRenderer); // Oyun d�ng�s�ne ba�la
		event(mRenderer); // olaylar� dinle
	}
	
}