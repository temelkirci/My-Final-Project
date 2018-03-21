#include "Player.h"

Player :: Player()
{
	mPlayerSpeed = 0.5;

	mPlayerPositiveSpeedX = mPlayerSpeed;
	mPlayerNegativeSpeedY = mPlayerSpeed;

	mPlayerPositiveSpeedY = mPlayerSpeed;
	mPlayerNegativeSpeedX = mPlayerSpeed;

	mPlayerThirsty = 80;
	mPlayerHealth = 70;
	mPlayerHunger = 90;
	
	mPlayerHungerTime = 0;
	mPlayerThirstyTime = 0;

	mPlayerHandgunBullet = 30;
	mPlayerRifleBullet = 50;
	mPlayerShotgunBullet = 20;
	
	mPlayerPositionX = 625.0;
	mPlayerPositionY = 300.0;

	mPlayerAngle = 0;
	mPlayerTime = 0;
	mPlayerHealthTime = 0;

	mPlayerRect.x = 625;
	mPlayerRect.y = 300;
	mPlayerRect.w = 100;
	mPlayerRect.h = 100;

	mInformationRect.x = 0;
	mInformationRect.y = 250;
	mInformationRect.w = 200;
	mInformationRect.h = 300;

	mPlayerColor.r = 0;
	mPlayerColor.g = 0;
	mPlayerColor.b = 0;
	mPlayerColor.a = 255;

	mPlayerPoint.x = 50;
	mPlayerPoint.y = 50;

	mPlayerDeadRect.x = 400;
	mPlayerDeadRect.y = 100;
	mPlayerDeadRect.w = 500;
	mPlayerDeadRect.h = 200;

	mPlayerDirection = "sag";
	//active_bullet = false;
	mPlayerStatus = "move"; // move olarak baþlayacak
	mPlayerWeapon = "knife"; // barbaros elinde knife ile baþlayacak
}

Player::Player(const Player& pPlayer)
{

}

Player& Player::operator = (const Player& pPlayer)
{
	return *this;
}

Player :: ~Player()
{

}

bool Player :: loadPlayerWeapon(char* pPathFile , SDL_Renderer* rend , char* pPlayerWeaponName)
{
	SDL_Surface* tPlayerSurface = IMG_Load(pPathFile);
	if(tPlayerSurface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Oyun" , "barbaros_yukle_weapon yuklenemedi..!" , NULL);
		exit(0);
	}

	mPlayerTexture = SDL_CreateTextureFromSurface(rend , tPlayerSurface);
	SDL_FreeSurface(tPlayerSurface);

	if(mPlayerTexture != 0)
	{
		mPLayerWeaponMap[pPlayerWeaponName] = mPlayerTexture;
		return true;
	}
	return false;
}

void Player :: deathInformation(SDL_Renderer* ren)
{
	SDL_Surface* tPlayerDeadSurface = IMG_Load("assets/bilgi_kutusu.jpg");
	mPlayerDeadTexture = SDL_CreateTextureFromSurface(ren , tPlayerDeadSurface);	// yüzeyi renderleyerek texture oluştur	
	SDL_FreeSurface(tPlayerDeadSurface);
}

double Player::getPlayerXPos()
{
	return mPlayerPositionX;
}

double Player::getPlayerYPos()
{
	return mPlayerPositionY;
}

void Player :: playerInformation(SDL_Renderer* pRenderer)
{
	SDL_Surface* daySurface;
	SDL_Texture* dayTexture;

	SDL_Surface* hourSurface;
	SDL_Texture* hourTexture;

		SDL_Rect tDayTextRect;
		tDayTextRect.x = 1200;
		tDayTextRect.y = 0;
		tDayTextRect.h = 30;

			// DAY
			string day_text = to_string(getDay());
			string gün = "Day : " + day_text;
			tDayTextRect.w = 10*(gün.length());
			daySurface = TTF_RenderText_Blended(mPlayerFont, gün.c_str() , mPlayerColor );
			dayTexture = SDL_CreateTextureFromSurface(pRenderer, daySurface );

			SDL_RenderCopyEx(pRenderer, dayTexture , NULL , &tDayTextRect, 0 , 0 , SDL_FLIP_NONE);

			// TIME
		SDL_Rect tTimeTextRect;
		tTimeTextRect.x = 1200;
		tTimeTextRect.y = 40;
		tTimeTextRect.h = 30;

			string saat_text = to_string(getHour());
			string saat_string = "Hour : ";
			string saat = "Hour : " + saat_text + " . 00";
			tTimeTextRect.w = 120;
			hourSurface = TTF_RenderText_Blended(mPlayerFont, saat.c_str() , mPlayerColor );
			hourTexture = SDL_CreateTextureFromSurface(pRenderer, hourSurface );

			SDL_RenderCopyEx(pRenderer, hourTexture , NULL , &tTimeTextRect, 0 , 0 , SDL_FLIP_NONE);
			

	SDL_FreeSurface(daySurface);
	SDL_DestroyTexture(dayTexture);

	SDL_FreeSurface(hourSurface);
	SDL_DestroyTexture(hourTexture);
	
}

void Player :: drawPlayer(SDL_Renderer* pRenderer, int pCameraX , int pCameraY)
{
	mPlayerRect.x = int(mPlayerPositionX) + pCameraX;
	mPlayerRect.y = int(mPlayerPositionY) + pCameraY;
	mPlayerRect.w = 100;
	mPlayerRect.h = 100;
	
	
	// Y EKSENİ İÇİN SINIR BELİRLEME
	if(mPlayerRect.y <= 0)
	{
		mPlayerRect.y=0;
		
		mPlayerNegativeSpeedX = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		mPlayerNegativeSpeedY = mPlayerSpeed;
		mPlayerPositiveSpeedX = 0;
	}

	if(mPlayerRect.x <= 0)
	{
		mPlayerRect.x=0;
		
		mPlayerNegativeSpeedX = 0;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		mPlayerNegativeSpeedY = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		
	}

	if(mPlayerRect.x <= 0 && mPlayerRect.y <= 0)
	{
		mPlayerRect.x = 0;
		mPlayerRect.y = 0;

		mPlayerNegativeSpeedX = 0;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		mPlayerNegativeSpeedY = mPlayerSpeed;
		mPlayerPositiveSpeedX = 0;
		
	}

	if(mPlayerRect.y >= 1400)
	{	
		mPlayerNegativeSpeedX = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		mPlayerNegativeSpeedY = 0;
		mPlayerPositiveSpeedX = mPlayerSpeed;
	}
	
	if(mPlayerRect.x >= 5900)
	{
		mPlayerNegativeSpeedX = mPlayerSpeed;
		mPlayerPositiveSpeedX = 0;
		mPlayerNegativeSpeedY = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
	}

	if(((mPlayerRect.x > 0) && (mPlayerRect.x < 5900)) && ((mPlayerRect.y > 0) && (mPlayerRect.y < 1400)))
	{		
		mPlayerNegativeSpeedX = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
		mPlayerNegativeSpeedY = mPlayerSpeed;
		mPlayerPositiveSpeedX = mPlayerSpeed;
	}

	if((mPlayerStatus == "move") && (mPlayerWeapon == "flashlight"))
	{
		if(mPlayerTime == 0 && mPlayerStatus == "move")
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 300 + pTime;
		}
		
		if(SDL_GetTicks() <= mPlayerTime && mPlayerStatus == "move") // 50 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime) && (SDL_GetTicks() <= (mPlayerTime + 300)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 300) && (SDL_GetTicks() <= (mPlayerTime + 600)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 600) && (SDL_GetTicks() <= (mPlayerTime + 900)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 900) && (SDL_GetTicks() <= (mPlayerTime + 1200)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			mPlayerStatus ="move";
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["move_flashlight_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}	
	}
	if((mPlayerStatus == "attack") && (mPlayerWeapon == "knife"))
	{		
		
		if(mPlayerTime == 0 && mPlayerStatus == "attack")
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 100 + pTime;
		}
		
		if(SDL_GetTicks() <= mPlayerTime && mPlayerStatus == "attack") // 50 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime) && (SDL_GetTicks() <= (mPlayerTime + 100)) && mPlayerStatus == "attack")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 100) && (SDL_GetTicks() <= (mPlayerTime + 200)) && mPlayerStatus == "attack")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 200) && (SDL_GetTicks() <= (mPlayerTime + 300)) && mPlayerStatus == "attack")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 300) && (SDL_GetTicks() <= (mPlayerTime + 400)) && mPlayerStatus == "attack")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife5"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			mPlayerStatus ="move";
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["knife1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}	
	}

	if((mPlayerStatus == "move") && (mPlayerWeapon == "knife"))
	{		
		if(mPlayerTime == 0 )
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 50 + pTime;
		}
		
		if(SDL_GetTicks() <= mPlayerTime && mPlayerStatus == "move") // 50 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime) && (SDL_GetTicks() <= (mPlayerTime + 50)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 50) && (SDL_GetTicks() <= (mPlayerTime + 100)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 100) && (SDL_GetTicks() <= (mPlayerTime + 150)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 150) && (SDL_GetTicks() <= (mPlayerTime + 200)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 200) && (SDL_GetTicks() <= (mPlayerTime + 250)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_5"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 250) && (SDL_GetTicks() <= (mPlayerTime + 300)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_6"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 300) && (SDL_GetTicks() <= (mPlayerTime + 350)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_7"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 350) && (SDL_GetTicks() <= (mPlayerTime + 400)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_8"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 400) && (SDL_GetTicks() <= (mPlayerTime + 450)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_9"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 450) && (SDL_GetTicks() <= (mPlayerTime + 500)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_10"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 500) && (SDL_GetTicks() <= (mPlayerTime + 550)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_11"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 550) && (SDL_GetTicks() <= (mPlayerTime + 600)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_12"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 600) && (SDL_GetTicks() <= (mPlayerTime + 650)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_13"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 650) && (SDL_GetTicks() <= (mPlayerTime + 700)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_14"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 700) && (SDL_GetTicks() <= (mPlayerTime + 750)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_15"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 750) && (SDL_GetTicks() <= (mPlayerTime + 800)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_16"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 800) && (SDL_GetTicks() <= (mPlayerTime + 850)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_17"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 850) && (SDL_GetTicks() <= (mPlayerTime + 900)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_18"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((SDL_GetTicks() > mPlayerTime + 900) && (SDL_GetTicks() <= (mPlayerTime + 950)) && mPlayerStatus == "move")
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_19"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_knife_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
			if(mPlayerStatus == "attack")
				mPlayerStatus = "attack";
		}
	}

	if((mPlayerStatus == "attack") && (mPlayerWeapon == "handgun"))
	{
		
		if(mPlayerTime == 0)
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 100 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["handgun1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 100))) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["handgun2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 100) && (pTime <= (mPlayerTime + 200)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["handgun3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			mPlayerStatus ="move";
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["handgun1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}

	if((mPlayerStatus == "move") && (mPlayerWeapon == "handgun"))
	{
		if(mPlayerTime == 0 )
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 200 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 200)) ) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 200) && (pTime <= (mPlayerTime + 400)) )
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 400) && (pTime <= (mPlayerTime + 600)) )
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 600) && (pTime <= (mPlayerTime + 800)) )
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			mPlayerTime = 0;
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_handgun_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}
	if((mPlayerStatus == "attack") && (mPlayerWeapon == "shotgun"))
	{
		if(mPlayerTime == 0)
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 200 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["shotgun1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 200))) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["shotgun2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 200) && (pTime <= (mPlayerTime + 400)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["shotgun3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			mPlayerStatus ="move";
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["shotgun1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}

	if((mPlayerStatus == "move") && (mPlayerWeapon == "shotgun"))
	{
		if(mPlayerTime == 0)
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 200 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 200 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 200))) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 200) && (pTime <= (mPlayerTime + 400)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 400) && (pTime <= (mPlayerTime + 600)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 600) && (pTime <= (mPlayerTime + 800)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			mPlayerTime = 0;
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_shotgun_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}

	if((mPlayerStatus == "attack") && (mPlayerWeapon == "rifle"))
	{
		
		if(mPlayerTime == 0)
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 100 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["rifle1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 100))) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["rifle2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 100) && (pTime <= (mPlayerTime + 200)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["rifle3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else
		{
			mPlayerTime = 0;
			mPlayerStatus ="move";
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["rifle1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}

	if((mPlayerStatus == "move") && (mPlayerWeapon == "rifle"))
	{
		if(mPlayerTime == 0)
		{
			pTime = SDL_GetTicks();
			mPlayerTime = 200 + pTime;
		}
		
		if(pTime <= mPlayerTime) // 100 ms sayarsa
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime) && (pTime <= (mPlayerTime + 200))) 
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_1"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 200) && (pTime <= (mPlayerTime + 400)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_2"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 400) && (pTime <= (mPlayerTime + 600)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_3"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
		else if((pTime > mPlayerTime + 600) && (pTime <= (mPlayerTime + 800)))
		{
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_4"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	
		else
		{
			mPlayerTime = 0;
			SDL_RenderCopyEx(pRenderer , mPLayerWeaponMap["idle_rifle_0"] , NULL , &mPlayerRect , mPlayerAngle , &mPlayerPoint , SDL_FLIP_NONE);
		}
	}
}

void Player :: updatePLayer(SDL_Renderer* pRenderer , Uint32 pPlayerTime)
{
	if(mPlayerHealth <= 0)
	{
		//Mix_Pause(1);
		//Mix_Pause(2);
		//Mix_Pause(3);

		mPlayerHealth = 0;
		mPlayerHealth = 0;
		
		SDL_RenderCopyEx(pRenderer, mPlayerDeadTexture , NULL , &mPlayerDeadRect , 0 , 0 , SDL_FLIP_NONE);
		
			string tDeadText = "You are dead :(";
			
			SDL_Rect tTextRect;
			tTextRect.x = mPlayerDeadRect.x + 100;
			tTextRect.y = mPlayerDeadRect.y + 70;
			tTextRect.h = 50;
			tTextRect.w = 300;

			SDL_Surface* tTextSurface = TTF_RenderText_Blended(mPlayerFont, tDeadText.c_str() , mPlayerColor );
			SDL_Texture* tTextTexture = SDL_CreateTextureFromSurface(pRenderer, tTextSurface);
			SDL_FreeSurface(tTextSurface);

			SDL_RenderCopyEx(pRenderer, tTextTexture, NULL , &tTextRect, 0 , 0 , SDL_FLIP_NONE);
			
	}
	else
	{
	
		if(mPlayerHealth > 100)
			mPlayerHealth = 100;
		if(mPlayerThirsty > 100)
			mPlayerThirsty = 100;
		if(mPlayerHunger > 100)
			mPlayerHunger = 100;

		if(mPlayerHungerTime == 0)
			mPlayerHungerTime = pPlayerTime + 7000; // açlýk her 7 saniyede 1 azalacak

		if(mPlayerThirstyTime == 0)
			mPlayerThirstyTime = pPlayerTime + 5000; // susuzluk her 5 saniyede 1 azalacak

		if(pPlayerTime >= mPlayerHungerTime)
		{
			mPlayerHunger--;
			if(mPlayerHunger <= 0)
				mPlayerHunger = 0;
			
			mPlayerHungerTime = 0;
			if(mPlayerHunger <= 25)
				mPlayerHealth--;

		}

		if(pPlayerTime >= mPlayerThirstyTime)
		{
			mPlayerThirsty--;
			if(mPlayerThirsty <= 0)
				mPlayerThirsty = 0;

			mPlayerThirstyTime = 0;
			if(mPlayerThirsty <= 25)
				mPlayerHealth--;

		}
		/*
		if((handgun_mermi <= 0) && (pPlayerWeapons == "handgun"))
		{		
			//writeText(render , time_barbaros , "Tabanca mermisi bitti" , 3000);
		}
		else if((rifle_mermi <= 0) && (pPlayerWeapons == "rifle"))
		{		
			//writeText(render , time_barbaros , "Tüfek mermisi bitti" , 3000);
		}
		else if((shotgun_mermi <= 0) && (pPlayerWeapons == "shotgun"))
		{		
			//writeText(render , time_barbaros , "Pompali tüfek mermisi bitti" , 3000);
		}
		*/
		
	}
}
         
double Player::getPlayerSpeed()
{
	return mPlayerSpeed;
}

void Player :: loadPlayer(SDL_Renderer* renderer)
{
	loadPlayerWeapon("assets/barbaros/flashlight/move/survivor-move_flashlight_0.png", renderer, "move_flashlight_0");
	loadPlayerWeapon("assets/barbaros/flashlight/move/survivor-move_flashlight_5.png", renderer, "move_flashlight_1");
	loadPlayerWeapon("assets/barbaros/flashlight/move/survivor-move_flashlight_10.png", renderer, "move_flashlight_2");
	loadPlayerWeapon("assets/barbaros/flashlight/move/survivor-move_flashlight_15.png", renderer, "move_flashlight_3");
	loadPlayerWeapon("assets/barbaros/flashlight/move/survivor-move_flashlight_19.png", renderer, "move_flashlight_4");

	loadPlayerWeapon("assets/barbaros/handgun/shoot/handgun_1.png", renderer, "handgun1");
	loadPlayerWeapon("assets/barbaros/handgun/shoot/handgun_2.png", renderer, "handgun2");
	loadPlayerWeapon("assets/barbaros/handgun/shoot/handgun_3.png", renderer, "handgun3");

	loadPlayerWeapon("assets/barbaros/handgun/idle/idle_handgun_0.png", renderer, "idle_handgun_0");
	loadPlayerWeapon("assets/barbaros/handgun/idle/idle_handgun_5.png", renderer, "idle_handgun_1");
	loadPlayerWeapon("assets/barbaros/handgun/idle/idle_handgun_10.png", renderer, "idle_handgun_2");
	loadPlayerWeapon("assets/barbaros/handgun/idle/idle_handgun_15.png", renderer, "idle_handgun_3");
	loadPlayerWeapon("assets/barbaros/handgun/idle/idle_handgun_19.png", renderer, "idle_handgun_4");
	
	loadPlayerWeapon("assets/barbaros/shotgun/shoot/shoot_shotgun_0.png", renderer, "shotgun1");
	loadPlayerWeapon("assets/barbaros/shotgun/shoot/shoot_shotgun_1.png", renderer, "shotgun2");
	loadPlayerWeapon("assets/barbaros/shotgun/shoot/shoot_shotgun_2.png", renderer, "shotgun3");

	loadPlayerWeapon("assets/barbaros/shotgun/idle/idle_shotgun_0.png", renderer, "idle_shotgun_0");
	loadPlayerWeapon("assets/barbaros/shotgun/idle/idle_shotgun_5.png", renderer, "idle_shotgun_1");
	loadPlayerWeapon("assets/barbaros/shotgun/idle/idle_shotgun_10.png", renderer, "idle_shotgun_2");
	loadPlayerWeapon("assets/barbaros/shotgun/idle/idle_shotgun_15.png", renderer, "idle_shotgun_3");
	loadPlayerWeapon("assets/barbaros/shotgun/idle/idle_shotgun_19.png", renderer, "idle_shotgun_4");

	loadPlayerWeapon("assets/barbaros/rifle/shoot/shoot_rifle_0.png", renderer, "rifle1");
	loadPlayerWeapon("assets/barbaros/rifle/shoot/shoot_rifle_1.png", renderer, "rifle2");
	loadPlayerWeapon("assets/barbaros/rifle/shoot/shoot_rifle_2.png", renderer, "rifle3");

	loadPlayerWeapon("assets/barbaros/rifle/idle/idle_rifle_0.png", renderer, "idle_rifle_0");
	loadPlayerWeapon("assets/barbaros/rifle/idle/idle_rifle_5.png", renderer, "idle_rifle_1");
	loadPlayerWeapon("assets/barbaros/rifle/idle/idle_rifle_10.png", renderer, "idle_rifle_2");
	loadPlayerWeapon("assets/barbaros/rifle/idle/idle_rifle_15.png", renderer, "idle_rifle_3");
	loadPlayerWeapon("assets/barbaros/rifle/idle/idle_rifle_19.png", renderer, "idle_rifle_4");

	loadPlayerWeapon("assets/barbaros/knife/meleeattack/meleeattack_knife_0.png", renderer, "knife1");
	loadPlayerWeapon("assets/barbaros/knife/meleeattack/meleeattack_knife_3.png", renderer, "knife2");
	loadPlayerWeapon("assets/barbaros/knife/meleeattack/meleeattack_knife_6.png", renderer, "knife3");
	loadPlayerWeapon("assets/barbaros/knife/meleeattack/meleeattack_knife_9.png", renderer, "knife4");
	loadPlayerWeapon("assets/barbaros/knife/meleeattack/meleeattack_knife_12.png", renderer, "knife5");

	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_0.png", renderer, "idle_knife_0");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_1.png", renderer, "idle_knife_1");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_2.png", renderer, "idle_knife_2");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_3.png", renderer, "idle_knife_3");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_4.png", renderer, "idle_knife_4");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_5.png", renderer, "idle_knife_5");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_6.png", renderer, "idle_knife_6");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_7.png", renderer, "idle_knife_7");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_8.png", renderer, "idle_knife_8");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_9.png", renderer, "idle_knife_9");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_10.png", renderer, "idle_knife_10");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_11.png", renderer, "idle_knife_11");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_12.png", renderer, "idle_knife_12");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_13.png", renderer, "idle_knife_13");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_14.png", renderer, "idle_knife_14");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_15.png", renderer, "idle_knife_15");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_16.png", renderer, "idle_knife_16");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_17.png", renderer, "idle_knife_17");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_18.png", renderer, "idle_knife_18");
	loadPlayerWeapon("assets/barbaros/knife/idle/idle_knife_19.png", renderer, "idle_knife_19");

	mPlayerFont = TTF_OpenFont("fonts/fontss.ttf", 140);
}