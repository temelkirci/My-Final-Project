#include "Inventory.h"

Inventory* Inventory::mInstanceInventory = nullptr;

Inventory::Inventory()
{
	envanter_durum = "9_envanter";
	mMaximumInventoryItemCapacity = 9;
	mInventoryItemNumber = 0; 
	mRectInventory.y = 670;
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

Inventory* Inventory::getInstanceInventory()
{
	if (mInstanceInventory == 0)
		mInstanceInventory = new Inventory();

	return mInstanceInventory;
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
		envanter_draw[pInventoryName] = mInventoryTexture; // Tüm textureleri saklayacaðýmýz yer
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

void Inventory::updateInventory(SDL_Renderer* pRenderer)
{
	SDL_Rect esya;
	SDL_Rect yazi;

	int x;
	int a = 0;

	if (mMaximumInventoryItemCapacity == 18)
	{
		x = 110;
		mRectInventory.x = x;
	}
	else if (mMaximumInventoryItemCapacity == 12)
	{
		x = 302;
		mRectInventory.x = x;
	}
	else if (mMaximumInventoryItemCapacity == 9)
	{
		x = 397;
		mRectInventory.x = x;
	}
	// esyanin yuksekliði 30
	// esyanin genisliði 40

	for (int t = 0; t<mMaximumInventoryItemCapacity; t++)
	{
		esya.x = x + a;
		esya.y = 685;
		esya.w = 40;
		esya.h = 30;

		if (ItemVector[t].numberItem > 0) // eþya sayýsý 1 den fazlaysa
		{
			ItemVector[t].xCoordItem = esya.x; // esya x-koordinatý
			ItemVector[t].yCoordItem = esya.y; // esya y-koordinatý

			SDL_SetTextureBlendMode(ItemVector[t].textureItem, SDL_BLENDMODE_BLEND);
			SDL_RenderCopyEx(pRenderer, ItemVector[t].textureItem, NULL, &esya, 0, 0, SDL_FLIP_NONE);	// eþyayý çiz

			yazi.x = esya.x - 7;
			yazi.y = esya.y - 13;
			yazi.w = 10;
			yazi.h = 12;

			string adet_deger = to_string(ItemVector[t].numberItem);
			char* adet_yaz = _strdup(adet_deger.c_str());

			SDL_Surface* textSurface = TTF_RenderText_Blended(mFont , adet_yaz , mInventoryColor );
			textTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
			SDL_FreeSurface(textSurface);

			SDL_RenderCopyEx(pRenderer, textTexture, NULL, &yazi, 0, 0, SDL_FLIP_NONE);
			SDL_DestroyTexture(textTexture);

			a = a + 65;
		}

		else if (ItemVector[t].numberItem <= 0) // eþya yoksa
		{
			ItemVector[t].nameItem = ""; // eþya ismini sýfýrla
			ItemVector[t].textureItem = NULL; // eþya textureyi sýfýrla
			ItemVector[t].numberItem = 0; // eþya sayýsýný 0 yap
			ItemVector[t].xCoordItem = NULL; // esya x-koordinatý
			ItemVector[t].yCoordItem = NULL; // esya y-koordinatý
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

	loadInventory("assets/18_envanter.png", "full_envanter", renderer);
	loadInventory("assets/12_envanter.png", "12_envanter", renderer);
	loadInventory("assets/9_envanter.png", "9_envanter", renderer);
	loadInventory("assets/envanter1.jpg", "Inventory", renderer);
}