#include "Items.h"

Items :: Items()
{
	SDL_Rect tTempRect = {900,300,100,100};
	setSolidItems("huge_box" , "blend" , 1 , 100 , true , tTempRect, NULL);

	
	// COLLECTÝBLE ITEMS
	tTempRect.x = 650;
	tTempRect.y = 350;
	tTempRect.w = 50;
	tTempRect.h = 30;
	
	setCollectibleItems("rifle" , "blend" , 1 , 100 , true , tTempRect, NULL);

	
	tTempRect.x = 50;
	tTempRect.y = 350;
	tTempRect.w = 50;
	tTempRect.h = 30;
	
	setCollectibleItems("handgun" , "blend" , 1 , 100 , true , tTempRect, NULL);
	

	tTempRect.x = 150;
	tTempRect.y = 650;
	tTempRect.w = 50;
	tTempRect.h = 30;

	setCollectibleItems("shotgun" , "blend" , 1 , 100 , true , tTempRect, NULL);
	

	tTempRect.x = 750;
	tTempRect.y = 350;
	tTempRect.w = 50;
	tTempRect.h = 30;

	setCollectibleItems("soup" , "blend" , 1 , 100 , true , tTempRect, NULL);


	tTempRect.x = 950;
	tTempRect.y = 550;
	tTempRect.w = 50;
	tTempRect.h = 30;

	setCollectibleItems("health_bag" , "blend" , 1 , 100 , true , tTempRect, NULL);

	bulletHandgun.bulletName = "bullet_handgun";
	bulletHandgun.bulletActive = false;
	
	bulletRifle.bulletName = "bullet_rifle";
	bulletRifle.bulletActive = false;

	bulletShotgun.bulletName = "bullet_shotgun";
	bulletShotgun.bulletActive = false;

	// UNCOLLECTÝBLE ITEMS
	tTempRect.x = 450;
	tTempRect.y = 550;
	tTempRect.w = 100;
	tTempRect.h = 100;

	setUnCollectibleItems("crater" , "blend" , 1 , 100 , true , tTempRect, NULL);

	mInformation = "";		
}

Items::Items(const Items& pItems)
{

}

Items& Items::operator = (const Items& pItems)
{
	return *this;
}

Items :: ~Items()
{

}

void Items :: setCollectibleItems(string pName , string pMode , int pNumber , int pHealth , bool pActive , SDL_Rect pPosition , SDL_Texture* pTexture)
{
	item.itemName = pName;
	item.itemBlendMode = pMode;
	item.itemNumber = pNumber;
	item.itemHealth = pHealth;
	item.itemActive = pActive;
	item.itemRect = pPosition;
	item.itemTexture = pTexture;

	mItemRectVector.push_back(pPosition);
	mCollectibleVector.push_back(item);
}

void Items::setUnCollectibleItems(string pName, string pMode, int pNumber, int pHealth, bool pActive, SDL_Rect pPosition, SDL_Texture* pTexture)
{
	item.itemName = pName;
	item.itemBlendMode = pMode;
	item.itemNumber = pNumber;
	item.itemHealth = pHealth;
	item.itemActive = pActive;
	item.itemRect = pPosition;
	item.itemTexture = pTexture;

	mItemRectVector.push_back(pPosition);
	mUnCollectibleVector.push_back(item);
}

void Items::setSolidItems(string pName, string pMode, int pNumber, int pHealth, bool pActive, SDL_Rect pPosition, SDL_Texture* pTexture)
{
	item.itemName = pName;
	item.itemBlendMode = pMode;
	item.itemNumber = pNumber;
	item.itemHealth = pHealth;
	item.itemActive = pActive;
	item.itemRect = pPosition;
	item.itemTexture = pTexture;

	mItemRectVector.push_back(pPosition);
	mSolidVector.push_back(item);
}

void Items :: itemInformation(string pItemName)
{
	if(pItemName == "health_bag")
	{
		mInformation = "Bu saglik cantasi karakterinizin sagligini 20 arttirir";
	}
	else if(pItemName == "handgun")
	{
		mInformation = "Bu silah zayif gorunuyor ama bununla kendimi bir sure koruyabilirim";
	}
	else if(pItemName == "shotgun")
	{
		mInformation = "Saldiri gucu yuksek bir silah . Yaratiklar benden korkacak";
	}
	else if(pItemName == "rifle")
	{
		mInformation = "Bu silah ile hizli ates edebilirim";
	}
	else if(pItemName == "kuru_agac")
	{
		mInformation = "Bu agac kurumus . Hicbir isime yaramaz";
	}
	else if(pItemName == "bread")
	{
		mInformation = "Bununla acligimi bir süre azaltabilirim";
	}
	else if(pItemName == "rock_1")
	{
		mInformation = "Ise yarar bir kaya parcasi";
	}
	else if(pItemName == "water")
	{
		mInformation = "Su temiz gorunuyor";
	}
	else if(pItemName == "soup")
	{
		mInformation = "Soguk corba.Bugun sansli gunumdeyim";
	}
}
