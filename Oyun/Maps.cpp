#include "Maps.h"

Maps::Maps()
{
	mCurrentCursor = "shoot";

	mMainMapRect.x = 0;
	mMainMapRect.y = 0;
	mMainMapRect.h = 3000;
	mMainMapRect.w = 6000;

	mMainCameraRect.x = 0;
	mMainCameraRect.y = 0;
	mMainCameraRect.h = 700;
	mMainCameraRect.w = 1350;

	mMouseRect.x = 600;
	mMouseRect.y = 300;
	mMouseRect.h = 30;
	mMouseRect.w = 30;
}

Maps::~Maps()
{

}

SDL_Rect Maps::getMouseRect()
{
	return mMouseRect;
}

double Maps::getMousePositionX()
{
	return mMouseRect.x;
}

double Maps::getMousePositionY()
{
	return mMouseRect.y;
}

void Maps::drawMap(SDL_Renderer* pRenderer)
{
	// barbaros genislik 100
	// barbaros yukseklik 100
	// ekran yukseklik 700
	// ekran genislik 1350
	// arkaplan genislik 6000
	// arkaplan yukseklik 3000
	
	if ((int)getPlayerXPos() < 300)
	{
		mMainCameraRect.y = 0;
	}

	if ((int)getPlayerYPos() < 625)
	{
		mMainCameraRect.x = 0;
	}

	if ((int)getPlayerYPos() >= 1100)
	{
		mMainCameraRect.y = -800;
		if ((int)getPlayerYPos() >= 1400)
			mPlayerPositionY = 1400;
	}

	if ((((int)getPlayerYPos() >= 300) && ((int)getPlayerYPos() < 1100)))
	{
		mMainCameraRect.y = -((int)getPlayerYPos() - 300);
	}

	if ((int)getPlayerXPos() >= 5275)
	{
		mMainCameraRect.x = -4650;
	}

	if ((int)getPlayerXPos() >= 5900) // haritanýn en saðýndan çýkmamasý için kontrol yapýlýyor
	{
		mPlayerPositionX = 5900;
	}

	if (((625 <= (int)getPlayerXPos()) && ((int)getPlayerXPos() < 5275)))
	{
		mMainCameraRect.x = -((int)getPlayerXPos() - 625);
	}

	if (mMainCameraRect.x >= 0 && mMainCameraRect.x <= 625)
	{
		mMainMapRect.x = -300;
	}
	else
	{
		mMainMapRect.x = ((-mMainCameraRect.x) / 300 - 1) * 300;
	}

	if (mMainCameraRect.y >= 0 && mMainCameraRect.y <= 300)
	{
		mMainMapRect.y = 0;
	}
	else
	{
		mMainMapRect.y = ((-mMainCameraRect.y) / 200) * 200;
	}
	/*
	//SDL_RenderSetClipRect(ren , &map);

	for (int i = 0; i<map_row; i++) // satır = 5
	{
		for (int j = 0; j<map_column; j++) // sütun = 6
		{
			mMainMapRect.x = mMainMapRect.x + map.w;

			map.x = mMainMapRect.x + mMainCameraRect.x;
			map.y = mMainMapRect.y + mMainCameraRect.y;

			SDL_RenderCopyEx(ren, texture_background, NULL, &map, 0, 0, SDL_FLIP_NONE);
		}
		mMainMapRect.x = ((-mMainCameraRect.x) / 300 - 1) * 300;
		mMainMapRect.y = mMainMapRect.y + map.h;
	}
	mMainMapRect.x = ((-mMainCameraRect.x) / 300 - 1) * 300;
	mMainMapRect.y = ((-mMainCameraRect.y) / 200) * 200;

	*/

	SDL_RenderCopyEx(pRenderer, mMapsMap["desert"], NULL, &mMainCameraRect, 0, 0, SDL_FLIP_NONE);
}

void Maps::drawMapObjects(SDL_Renderer* pRenderer)
{
	drawPlayer(pRenderer , mMainCameraRect.x , mMainCameraRect.y);
}

double Maps::getMapPositionX()
{
	return mMainMapRect.x;
}

double Maps::getMapPositionY()
{
	return mMainMapRect.y;
}

double Maps::getCameraPositionX()
{
	return mMainCameraRect.x;
}

double Maps::getCameraPositionY()
{
	return mMainCameraRect.y;
}

void Maps::drawCursor(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, mMapsMap[mCurrentCursor], NULL, &mMouseRect, 0, 0, SDL_FLIP_NONE);
}

void Maps::loadMapFiles(char* pMapFilePath, SDL_Renderer* pRenderer, char* pMapName)
{
	SDL_Surface* tMapSurface = IMG_Load(pMapFilePath);
	if (tMapSurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Maps", pMapName, NULL);
		exit(0);
	}

	SDL_Texture* tMapTexture = SDL_CreateTextureFromSurface(pRenderer, tMapSurface);
	SDL_FreeSurface(tMapSurface);

	if (tMapTexture != 0)
	{
		mMapsMap[pMapName] = tMapTexture;
	}
}

void Maps::loadMaps(SDL_Renderer* pRenderer)
{
	loadMapFiles("assets/desert.jpg", pRenderer, "desert");
	loadMapFiles("assets/cursor.png", pRenderer, "shoot");
	loadMapFiles("assets/Sepia.png", pRenderer, "sepia");
}