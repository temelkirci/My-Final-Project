#include "Fonts.h"

Fonts :: Fonts()
{
	mFont = TTF_OpenFont("fonts/Roboto-Regular.ttf", 100);

	toplam = 0;

	mBackColor.r = 0;
	mBackColor.g = 0;
	mBackColor.b = 0;
	mBackColor.a = 255;

	mBackRect.x = 0;
	mBackRect.y = 0;
	mBackRect.w = 100;
	mBackRect.h = 30;

	arkaPlan.x = 0;
	arkaPlan.y = 0;
	arkaPlan.w = 180;
	arkaPlan.h = 160;

	dizi[0] = "health";
	dizi[1] = "hunger";
	dizi[2] = "thirsty";
	dizi[3] = "bullet";
	
}

Fonts::Fonts(const Fonts& pFonts)
{

}

Fonts& Fonts::operator = (const Fonts& pFonts)
{
	return *this;
}

Fonts :: ~Fonts()
{
	TTF_CloseFont(mFont); // Yazi fontunu kapatýr
}

int Fonts :: loadImage(char* pPathFile, string pImageName, SDL_Renderer* pRender)
{
	SDL_Surface* tImageSurface = IMG_Load(pPathFile);

	if(tImageSurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Fonts" , "Sol üst resimler yuklenemedi..!" , NULL);
		exit(0);
	}

	mImageTexture = SDL_CreateTextureFromSurface(pRender, tImageSurface);
	SDL_FreeSurface(tImageSurface);

	if(mImageTexture != 0)
	{
		mImageMap[pImageName] = mImageTexture;
		return true;
	}
	return false;

}

void Fonts ::playerStatus(SDL_Renderer* pRenderer ,
							 int pX , int pY , 
							 int pWidth , int pHeight ,
							 int pHealth , int pBullet , int pHungury , int pThirsty)

{
		mHealthRect.w = pBullet; // source rect
		mHungerRect.w = pHungury;
		mThirstyRect.w = pThirsty;

	for(int i=0; i<4 ; i++)
	{
		SDL_Rect tText;
		tText.x = pX;
		tText.y = pY;
		tText.w = pWidth;
		tText.h = pHeight;

		SDL_RenderCopyEx(pRenderer , mImageMap[dizi[i]] , NULL , &tText , 0 , 0 , SDL_FLIP_NONE); // saðlik resm , susuzluk resmi , açlýk resmi , mermi resmi
				
		// Saglýk , Mermi , Açlýk ve Susuzluk deðerleri
		mBackRect.x = pX+pWidth+10;
		mBackRect.y = pY;
		mBackRect.w = 100;
		mBackRect.h = pHeight;

		if(dizi[i] == "health")
		{
			SDL_SetRenderDrawColor(pRenderer , 47 , 79 , 79 , 150); // gri arkaplan
		    SDL_RenderFillRect(pRenderer, &mBackRect);

			mHealthRect.x = pX+pWidth+10;
			mHealthRect.y = pY;
			mHealthRect.w = pHealth;
			mHealthRect.h = pHeight;

			SDL_SetRenderDrawColor(pRenderer , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(pRenderer, &mHealthRect);

		}
		else if(dizi[i] == "hunger")
		{
			SDL_SetRenderDrawColor(pRenderer , 47 , 79 , 79 , 150); // gri arkaplan
			SDL_RenderFillRect(pRenderer, &mBackRect);

			mHungerRect.x = pX+pHeight+10;
			mHungerRect.y = pY;
			mHungerRect.w = pHungury;
			mHungerRect.h = pHeight;

			SDL_SetRenderDrawColor(pRenderer , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(pRenderer, &mHungerRect);
		}
		else if(dizi[i] == "thirsty")
		{
			SDL_SetRenderDrawColor(pRenderer , 47 , 79 , 79 , 150); // gri arkaplan
			SDL_RenderFillRect(pRenderer, &mBackRect);

			mThirstyRect.x = pX+pWidth+10;
			mThirstyRect.y = pY;
			mThirstyRect.w = pThirsty;
			mThirstyRect.h = pHeight;

			SDL_SetRenderDrawColor(pRenderer , 255 , 0 , 0 , 200); // beyaz arkaplan
			SDL_RenderFillRect(pRenderer, &mThirstyRect);
		}

		else if(dizi[i] == "bullet")
		{
			SDL_Rect tText;
			tText.x=pX+pWidth+10;;
			tText.y=pY;
			tText.w=pWidth;
			tText.h=pHeight;
			
			string tTempBullet = to_string(pBullet);
			
			SDL_Surface* tTextSurface = TTF_RenderText_Blended(mFont , tTempBullet.c_str(), mBackColor );
			SDL_Texture* tTextTexture = SDL_CreateTextureFromSurface( pRenderer, tTextSurface);
			SDL_FreeSurface(tTextSurface);

			SDL_RenderCopyEx(pRenderer , tTextTexture, NULL , &tText , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(tTextTexture);
		}
		pY=pY+pHeight+20;
	}
}


void Fonts :: writeText(SDL_Renderer* pRender , Uint32 pTime , char* pText)
{
	if(pTime != 0)
	{
		if(toplam == 0) // ilk zamaný sakla
			toplam = pTime + 3000;
	
		// yazý ekranda 3 sn görünecek
		if(total <= toplam) // yazýnýn ekranda gözükme süresi
		{		
			SDL_Rect tText;
			tText.x=250;
			tText.y=0;
			tText.w=strlen(pText)*25;
			tText.h=30;

			SDL_Surface* tTextSurface = TTF_RenderText_Blended( mFont , pText, mBackColor );
			mTextTexture = SDL_CreateTextureFromSurface(pRender, tTextSurface);
			SDL_FreeSurface(tTextSurface);

			SDL_RenderCopyEx(pRender, mTextTexture, NULL , &tText , 0 , 0 , SDL_FLIP_NONE);	
		}
		else
		{
			toplam = 0;
			// nothing
		}
	}
	else
	{
		SDL_Rect tText;
		tText.x=550;
		tText.y=0;
		tText.w=100;
		tText.h=30;
			
			SDL_Surface* tTextSurface = TTF_RenderText_Blended( mFont , pText, mBackColor );
			mTextTexture = SDL_CreateTextureFromSurface(pRender, tTextSurface);
			SDL_FreeSurface(tTextSurface);

			SDL_RenderCopyEx(pRender, mTextTexture, NULL , &tText, 0 , 0 , SDL_FLIP_NONE);
	}
}

void Fonts :: loadFonts(SDL_Renderer* pRenderer)
{
	loadImage("assets/hunger.png", "hunger" , pRenderer); // açlýk icon'u
	loadImage("assets/bullet.png", "bullet" , pRenderer); // mermi icon'u
	loadImage("assets/health.png", "health" , pRenderer); // saðlýk icon'u
	loadImage("assets/drop.png", "thirsty" , pRenderer); // susuzluk icon'u
}