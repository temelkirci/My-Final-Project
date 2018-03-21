#include "Inventory.h"

Inventory::Inventory()
{
	envanter_durum = "9_envanter";
	mMaximumInventoryItemCapacity = 9;
	mInventoryItemNumber = 0; 

	mInventoryRect.y = 670;
	mInventoryRect.h = 50;
	mInventoryRect.w = 600;
}

Inventory::Inventory(const Inventory& pInventory)
{

}

Inventory& Inventory::operator = (const Inventory& pInventory)
{
	return *this;
}

Inventory :: ~Inventory()
{

}

SDL_Rect Inventory::getInventoryRect()
{
	return mInventoryRect;
}

int Inventory::getInventoryMaxSize()
{
	return mMaximumInventoryItemCapacity;
}

int Inventory::getInventoryCurrentSize()
{
	return mInventoryItemNumber;
}

void Inventory::loadInventory(const char* pPathFile , const char* pInventoryName , SDL_Renderer* pRender)
{
	SDL_Surface * tInventorySurface = IMG_Load(pPathFile);
	if (tInventorySurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Inventory", "Envanter yüklenemedi..!", NULL);
		exit(0);
	}
	mInventoryTexture = SDL_CreateTextureFromSurface(pRender, tInventorySurface);
	SDL_FreeSurface(tInventorySurface);
	
	if (mInventoryTexture != 0)
	{
		mInventoryMap[pInventoryName] = mInventoryTexture; // Tüm textureleri saklayacaðýmýz yer
	}
	
}

void Inventory::addItemtoInventory(string pItemName, int pItemNumber, SDL_Texture* pItemTexture)
{
	if (mInventoryItemNumber < mMaximumInventoryItemCapacity)
	{
		for (int i = 0; i<mInventoryItemNumber; i++)
		{
			if ((ItemVector[i].nameItem == "") && (ItemVector[i].numberItem <= 0)) // eþya envanterde yoksa
			{
				ItemVector[i].nameItem = pItemName;
				ItemVector[i].textureItem = pItemTexture;
				ItemVector[i].numberItem = pItemNumber;
				mInventoryItemNumber++;
				break;
			}
			else if (ItemVector[i].nameItem == pItemName) // eþya envanterde varsa
			{
				if (ItemVector[i].numberItem < 9) // her eþyadan maximum 9 tane olabilir
				{
					ItemVector[i].numberItem = ItemVector[i].numberItem + 1;
					break;
				}
				else
				{
					ItemVector[i].numberItem = 9;
					cout << pItemName << " sayisi 9 u gecemez" << endl;
				}
			}

		}
	}
	else
	{
		cout << "Envanter Dolu" << endl;
	}

}

void Inventory::drawInventory(SDL_Renderer* pRenderer)
{
	SDL_Rect esya;
	SDL_Rect yazi;

	int x;
	int a = 0;

	if (mMaximumInventoryItemCapacity == 18)
	{
		x = 110;
		mInventoryRect.x = x;
		SDL_RenderCopyEx(pRenderer, mInventoryMap["full_envanter"], NULL, &mInventoryRect, 0, 0, SDL_FLIP_NONE);
	}
	else if (mMaximumInventoryItemCapacity == 12)
	{
		x = 302;
		mInventoryRect.x = x;
		SDL_RenderCopyEx(pRenderer, mInventoryMap["12_envanter"], NULL, &mInventoryRect, 0, 0, SDL_FLIP_NONE);
	}
	else if (mMaximumInventoryItemCapacity == 9)
	{
		x = 397;
		mInventoryRect.x = x;
		SDL_RenderCopyEx(pRenderer, mInventoryMap["9_envanter"], NULL, &mInventoryRect, 0, 0, SDL_FLIP_NONE);
	}
	// esyanin yuksekliði 30
	// esyanin genisliði 40
	
	if (!ItemVector.empty())
	{
		for (int t = 0; t < mMaximumInventoryItemCapacity; t++)
		{
			esya.x = x + a;
			esya.y = 685;
			esya.w = 40;
			esya.h = 30;

			if (ItemVector[t].numberItem > 0) // eþya sayýsý 1 den fazlaysa
			{
				ItemVector[t].itemPositionRect.x = esya.x; // esya x-koordinatý
				ItemVector[t].itemPositionRect.y = esya.y; // esya y-koordinatý
				ItemVector[t].itemPositionRect.w = 40; // esya x-koordinatý
				ItemVector[t].itemPositionRect.h = 30; // esya y-koordinatý

				SDL_SetTextureBlendMode(ItemVector[t].textureItem, SDL_BLENDMODE_BLEND);
				SDL_RenderCopyEx(pRenderer, ItemVector[t].textureItem, NULL, &ItemVector[t].itemPositionRect, 0, 0, SDL_FLIP_NONE);	// eþyayý çiz

				yazi.x = esya.x - 7;
				yazi.y = esya.y - 13;
				yazi.w = 10;
				yazi.h = 12;

				string adet_deger = to_string(ItemVector[t].numberItem);
				char* adet_yaz = _strdup(adet_deger.c_str());

				SDL_Surface* tTextSurface = TTF_RenderText_Blended(mInventoryFont, adet_yaz, mInventoryColor);
				tTextTexture = SDL_CreateTextureFromSurface(pRenderer, tTextSurface);
				SDL_FreeSurface(tTextSurface);

				SDL_RenderCopyEx(pRenderer, tTextTexture, NULL, &yazi, 0, 0, SDL_FLIP_NONE); // eþya sayýsýný yazdýrýr

				a = a + 65;
			}

			else if (ItemVector[t].numberItem <= 0) // eþya yoksa
			{
				ItemVector[t].nameItem = ""; // eþya ismini sýfýrla
				ItemVector[t].textureItem = NULL; // eþya textureyi sýfýrla
				ItemVector[t].numberItem = 0; // eþya sayýsýný 0 yap
			}
		}
	}
}

void Inventory::deleteItem(string object_name, int delete_number)
{
	for (int t = 0; t<mInventoryItemNumber; t++)
	{
		if (ItemVector[t].nameItem == object_name)
		{
			ItemVector[t].numberItem = ItemVector[t].numberItem - delete_number;

			if (ItemVector[t].numberItem <= 0)
				mInventoryItemNumber--;

			break;
		}
	}

}

void Inventory::loadInventoryFiles(SDL_Renderer* renderer)
{
	// font yükle
	mInventoryFont = TTF_OpenFont("fonts/fontss.ttf", 140);

	loadInventory("assets/18_envanter.png", "full_envanter", renderer);
	loadInventory("assets/12_envanter.png", "12_envanter", renderer);
	loadInventory("assets/9_envanter.png", "9_envanter", renderer);
}