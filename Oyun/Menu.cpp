#include "Menu.h"

using namespace std;

Menu :: Menu()
{
	mMenuMusic = Mix_LoadMUS("assets/sounds/menu.ogg");
	
	SDL_ShowCursor(SDL_DISABLE);

	mMenuBackgroundRect.x = 0;
	mMenuBackgroundRect.y = 0;
	mMenuBackgroundRect.w = 1360;
	mMenuBackgroundRect.h = 750;

	mTextColor.r = 0;
	mTextColor.g = 0;
	mTextColor.b = 0;
	mTextColor.a = 100;

	mStartButton.x = 550;
	mStartButton.y = 200;
	mStartButton.w = 200;
	mStartButton.h = 50;

	mSaveButton.x = 550;
	mSaveButton.y = 280;
	mSaveButton.w = 200;
	mSaveButton.h = 50;

	mLoadButton.x = 550;
	mLoadButton.y = 360;
	mLoadButton.w = 200;
	mLoadButton.h = 50;

	mCreditsButton.x = 550;
	mCreditsButton.y = 440;
	mCreditsButton.w = 200;
	mCreditsButton.h = 50;

	mExitButton.x = 550;
	mExitButton.y = 520;
	mExitButton.w = 200;
	mExitButton.h = 50;

	mMouseCoord.x = 675;
	mMouseCoord.y = 345;

	mButtonArray[0] = "START";
	mButtonArray[1] = "SAVE";
	mButtonArray[2] = "LOAD";
	mButtonArray[3] = "CREDITS";
	mButtonArray[4] = "EXIT";

	mMenuTexture = NULL ;
}

Menu::Menu(const Menu& pMenu)
{

}

Menu& Menu::operator = (const Menu& pMenu)
{
	return *this;
}

Menu :: ~Menu()
{
	SDL_DestroyTexture(mMenuTexture);
	
	mMenuTexture = NULL ;
}

Menu* Menu::getInstanceMenu()
{
	if (mInstanceMenu == 0)
		mInstanceMenu = new Menu();

	return mInstanceMenu;
}

void Menu :: renderMenu(SDL_Renderer* pRender)
{
	SDL_ShowCursor(SDL_DISABLE);
	SDL_RenderClear(pRender); // renderi temizle

	SDL_RenderCopyEx(pRender, mMenuTexture , NULL , &mMenuBackgroundRect, 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderCopyEx(pRender, mButtonMap["START"] , NULL , &mStartButton, 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(pRender, mButtonMap["SAVE"] , NULL , &mSaveButton, 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(pRender, mButtonMap["LOAD"] , NULL , &mLoadButton, 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(pRender, mButtonMap["CREDITS"] , NULL , &mCreditsButton, 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(pRender, mButtonMap["EXIT"] , NULL , &mExitButton, 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderCopyEx(pRender, mButtonMap["sepia"] , NULL , &mMouseCoord, 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderPresent(pRender);
}

void Menu :: eventHandling()
{
	SDL_Event ev;

	int x , y;	

	SDL_GetMouseState(&x,&y);

	mMouseCoord.x=x;
	mMouseCoord.y=y;
	mMouseCoord.w=30;
	mMouseCoord.h=30;

	while(SDL_PollEvent(&ev) != 0)
	{
		switch(ev.type)
		{
			case SDL_QUIT :// sað üstteki çarpýya basarsa oyunu kapat
				
				GameState = GAME_STATE::EXIT;
				break;
			case SDL_MOUSEBUTTONDOWN:

				// Play tuþuna basýlýrsa
				if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&mMouseCoord, &mStartButton)))
				{
					Mix_HaltMusic(); // Arkaplan müziðini durdur
					Mix_PlayMusic(mMenuMusic, -1); // oyun müziðini baþlat
					
					SDL_ShowCursor(SDL_DISABLE);
					
					GameState = GAME_STATE::STARTING;
					break;					
					
				}
				// Credits tuþuna basýlýrsa
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&menü_mouse , &mSaveButton)))
				{	
					char* data_path = NULL;
					char* base_path = SDL_GetBasePath();
					if(base_path)
					{
						data_path = base_path;
						cout<<data_path<<endl;
					}
					else
					{
						data_path = SDL_strdup("./");
						cout<<data_path<<endl;
					}
					/*
					char* pref_path = NULL;
					char* base_path = SDL_GetPrefPath("Temel Game" , "My Awesome SDL2 Game");
					
					if(base_path)
					{
						pref_path = base_path;
						cout<<"Oyun Kaydedildi"<<endl;
					}
					else
					{
						cout<<"else"<<endl;
					}
					*/
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&menü_mouse , &mLoadButton)))
				{
					cout<<"Oyun Yükleniyor"<<endl;
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&menü_mouse , &mCreditsButton)))
				{
					cout<<"Oyun Hakkinda"<<endl;
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&menü_mouse , &mExitButton)))
				{
					GameState = GAME_STATE::EXIT;					
					break;
				}
				break;
		}
	}
}

void Menu::loadMenu(char* pPathFile, SDL_Renderer* pRenderer)
{
	mMenuFont = TTF_OpenFont("fonts/fontss.ttf", 100);

	SDL_Surface* tMenuSurface = IMG_Load(pPathFile);
	if (tMenuSurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Menu", "Menü yuklenemedi..!", NULL);
		exit(0);
	}
	mMenuTexture = SDL_CreateTextureFromSurface(pRenderer, tMenuSurface);
	SDL_FreeSurface(tMenuSurface);
}

bool Menu::loadPathMenu(char* pFileName, string pTextureName, SDL_Renderer* pRender)
{
	SDL_Surface* mButtonSurface = IMG_Load(pFileName);

	if (mButtonSurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Menu", "Menu :: load_buttons (surface_buttons yuklenemedi..!)", NULL);
		exit(0);
	}

	mButtonTexture = SDL_CreateTextureFromSurface(pRender, mButtonSurface);	// yüzeyi renderleyerek texture oluþtur	
	SDL_FreeSurface(mButtonSurface);

	if (mButtonTexture != 0)
	{
		mButtonMap[pTextureName] = mButtonTexture; // Tüm textureleri saklayacaðýmýz yer

		return true;
	}
	return false;
}

void Menu :: loadMenuItems(SDL_Renderer* renderer)
{
	loadMenu("assets/menu.jpg", renderer);
	loadPathMenu("assets/buttons/START.png", "START",renderer);
	loadPathMenu("assets/buttons/SAVE.png", "SAVE",renderer);
	loadPathMenu("assets/buttons/LOAD.png", "LOAD",renderer);
	loadPathMenu("assets/buttons/CREDITS.png", "CREDITS",renderer);
	loadPathMenu("assets/buttons/EXIT.png", "EXIT",renderer);
	loadPathMenu("assets/Sepia.png", "sepia", renderer);
}