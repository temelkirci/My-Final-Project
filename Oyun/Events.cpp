#include "Events.h"

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacağız

using namespace std;

Events::Events()
{
	mCurrentPlayerImage = "sag";
	mDrawing = "";

	mApplyDraw = false;
	mPlacement = false;
	mCancelDraw = false;
	mIsCollision = false;

	mPauseGame = false;
	mIsMove = false;
}

Events::~Events()
{
	
}

void Events :: event(SDL_Renderer* rend)
{
	mKey;
	int tPosX , tPosY;	

	SDL_GetMouseState(&tPosX,&tPosY);

	mSolidMouse.x = tPosX;
	mSolidMouse.y = tPosY;
	mSolidMouse.w = 30;
	mSolidMouse.h = 30;

	mMouseRect.x = tPosX - (int)getCameraPositionX();
	mMouseRect.y = tPosY - (int)getCameraPositionY();


	cout << mMouseRect.x << " , " << mMouseRect.y << endl;
	
	
	if(SDL_HasIntersection(&mSolidMouse , &(getInventoryRect()) )) // mouse envanterin üzerineyse ok imleci gözüksün
	{
		mCurrentCursor = "sepia";

		for(int t=0;t<getInventoryMaxSize();t++)
		{
			if (SDL_HasIntersection(&mSolidMouse, &ItemVector[t].itemPositionRect))
			{
				cout << "Ben " + ItemVector[t].nameItem << endl;
				break;
			}
		}
		
	}
	else
	{	
		mCurrentCursor = "shoot";
	}
	
	
	//// PLAYER DÖNME AÇISI VE YÖNÜ ////
	if((getPlayerXPos() + 50) <= mMouseRect.x) // mouse sağ tarafta ise
	{
		if((getPlayerYPos() + 50) <= mMouseRect.y) // 1.bölge (sağ-alt)
		{
			 mDistanceX = abs(mMouseRect.x - (getPlayerXPos() + 50));
			 mDistanceY = abs(mMouseRect.y - (getPlayerYPos() + 50));

			if(mDistanceX == 0)
				mDistanceX = 1;
			if(mDistanceY == 0)
				mDistanceY = 1;

			mTangent = mDistanceY / mDistanceX;
			mTangentAngle = (atan(mTangent) * 180) / PI ;
			mPlayerAngle = mTangentAngle;

		}

		else // 4.bölge (sağ-üst)
		{
			mDistanceX = abs(mMouseRect.x - (getPlayerXPos() + 50));
			mDistanceY = abs(mMouseRect.y - (getPlayerYPos() + 50));

			if(mDistanceX == 0)
				mDistanceX = 1;
			if(mDistanceY == 0)
				mDistanceY = 1;

			mTangent = mDistanceY / mDistanceX;
			mTangentAngle = (atan(mTangent) * 180) / PI ; // atan fonksiyonu ile y_distance / x_distance oranýna göre x eksenine göre açýyý hesaplýyoruz
			mPlayerAngle = 360 - mTangentAngle;
		
		}
	}

	else // mouse sol tarafta ise
	{
		if(getPlayerYPos() +50 <= mMouseRect.y) // 2.bölge (sol-alt)
		{
			mDistanceX = abs((getPlayerXPos() + 50) - mMouseRect.x);
			mDistanceY = abs(mMouseRect.y - (getPlayerYPos() + 50));

			if(mDistanceX == 0)
				mDistanceX = 1;
			if(mDistanceY == 0)
				mDistanceY = 1;

			mTangent = mDistanceY / mDistanceX;
			mTangentAngle = (atan(mTangent) * 180) / PI ; // atan fonksiyonu ile y_distance / x_distance oranýna göre x eksenine göre açýyý hesaplýyoruz
			mPlayerAngle = 180 - mTangentAngle;

		}

		else // 3.bölge (sol-üst)
		{
			mDistanceX = abs((getPlayerXPos() + 50) - mMouseRect.x);
			mDistanceY = abs(mMouseRect.y - (getPlayerYPos() + 50));

			if(mDistanceX == 0)
				mDistanceX = 1;
			if(mDistanceY == 0)
				mDistanceY = 1;

			mTangent = mDistanceY / mDistanceX;
			mTangentAngle = (atan(mTangent) * 180) / PI ;
			mPlayerAngle = 180 + mTangentAngle;

		}
	}
	
	/*
	if(((int)mPlayerPositionX+50) <= mTargetX && mIsMove) // mouse sağ tarafta ise
	{
		if(((int)mPlayerPositionY+50) <= mTargetY && mIsMove) // 1.bölge (sağ-alt)
		{
			mPlayerPositionX = mPlayerPositionX + ( mPlayerPositionX * cos(mPlayerAngle) ); 
			mPlayerPositionY = mPlayerPositionY + ( mPlayerPositionY * sin(mPlayerAngle) );
		}
		else if(((int)mPlayerPositionY+50) > mTargetY && mIsMove) // sağ-üst
		{
			mPlayerPositionX = mPlayerPositionX + ( mPlayerPositionX * cos(mPlayerAngle) );
			mPlayerPositionY = mPlayerPositionY - ( mPlayerPositionY * sin(mPlayerAngle) );
		}
	}
	else // mouse sol tarafta ise
	{
		if((int)mPlayerPositionY+50 <= mTargetY && mIsMove) // 2.bölge (sol-alt)
		{
			mPlayerPositionX = mPlayerPositionX - ( mPlayerPositionX * cos(mPlayerAngle) );
			mPlayerPositionY = mPlayerPositionY + ( mPlayerPositionY * sin(mPlayerAngle) );
		}
		else if((int)mPlayerPositionY+50 > mTargetY && mIsMove) // sol-üst
		{
			mPlayerPositionX = mPlayerPositionX - ( mPlayerPositionX * cos(mPlayerAngle) );
			mPlayerPositionY = mPlayerPositionY - ( mPlayerPositionY * sin(mPlayerAngle) );
		}
	}
	*/
	if ((mKey.button.button == SDL_BUTTON_RIGHT))
	{
		mCancelDraw = true;
		mIsMove = true;
		mTargetX = mMouseRect.x;
		mTargetY = mMouseRect.y;

		//mPlayerAngle = angle;
	}
	///// MOUSE A GÖRE HAREKET ////

	if(mPlayerPositionX+50 > mTargetX && mIsMove) // sola git
	{
		mPlayerPositionX = mPlayerPositionX - getPlayerSpeed();
		mPlayerDirection = "sol";
		
		if(!Mix_Playing(1) && getPlayerSpeed() != 0)
		{
			Mix_PlayChannel(1 , mWalkSound, 0);
		}
	}
	else if(mPlayerPositionX+50 < mTargetX && mIsMove) // sağa git
	{
		mPlayerPositionX = mPlayerPositionX + getPlayerSpeed();
		mPlayerDirection = "sag";

		if(!Mix_Playing(1) && getPlayerSpeed() != 0)
		{
			Mix_PlayChannel(1 , mWalkSound, 0);
		}
	}
	else
	{
		if(mPlayerPositionY+50 > mTargetY && mIsMove) // yukarı git
		{
			mPlayerPositionY = mPlayerPositionY - getPlayerSpeed();
			mPlayerDirection = "yukari";

			if(!Mix_Playing(1) && getPlayerSpeed() != 0)
			{
				Mix_PlayChannel(1 , mWalkSound, 0);
			}
		}
		else if(mPlayerPositionY+50 < mTargetY && mIsMove) // aşağı git
		{
			mPlayerPositionY = mPlayerPositionY + getPlayerSpeed();
			mPlayerDirection = "asagi";
		
			if(!Mix_Playing(1) && getPlayerSpeed() != 0)
			{
				Mix_PlayChannel(1 , mWalkSound, 0);
			}
		}
		else
		{
			mIsMove = false; // dont move
		}
	}
	
	////////////////////////
	/*
	if(drawing != "") // çizilecek eşya varsa
	{
		current_cursor = "sepia";
		if(!yerlestirme)
		{
			for(size_t j=0 ; j != solid.size() ; ++j)
			{
				if((solid[j].item_name == "")) // çizilecek item için indis bulma
				{
					solid[j].item_name = drawing;					
					indis_item = j;

					yerlestirme = true;
					collision = false;
					draw_apply = false;
					cancel_draw = false;

					break;
				}
			
			}
		}
		else // eşya bilgileri kaydedilmişse
		{
			solid[indis_item].item_active = false;
			solid[indis_item].item_blendmode = "add";
			solid[indis_item].number_item = 1;
				
			for(vector<Item>::iterator t = col.begin() ; t != col.end(); t++)
			{
				
				if((SDL_HasIntersection(&solid[indis_item].item_rect , &(*t).item_rect) ))
				{
					collision = true;
					break;
				}
				else if((SDL_HasIntersection(&solid[indis_item].item_rect , &(*t).item_rect)))
				{
					collision = true;
					break;
				}
				else if((SDL_HasIntersection(&solid[indis_item].item_rect , &player_barbaros)))
				{
					collision = true;
					break;
				}
				
			}
			
			
			if(collision == true)
				draw_apply = false;
		
			if(draw_apply) // eşyayı çiz
			{
				solid[indis_item].item_blendmode = "blend";
				solid[indis_item].item_active = true;
				solid[indis_item].item_rect.x = (mouse.x/25)*25; 
				solid[indis_item].item_rect.y = (mouse.y/12)*12;   
				solid[indis_item].item_rect.w = 100;
				solid[indis_item].item_rect.h = 100;
				
				if(solid[indis_item].item_blendmode == "wood_block")
					solid[indis_item].item_health = 1000;
				if(solid[indis_item].item_blendmode == "brick_block")
					solid[indis_item].item_health = 2000;
				if(solid[indis_item].item_blendmode == "stone_block")
					solid[indis_item].item_health = 3000;
				if(solid[indis_item].item_blendmode == "iron_block")
					solid[indis_item].item_health = 4000;
				if(solid[indis_item].item_blendmode == "steel_block")
					solid[indis_item].item_health = 5000;
				

				for(int i=0;i<inventory_size;i++)
				{
					if(InventoryObject[i].objectName == drawing)
					{
						indis_item = i;
						break;
					}
				}
				deleteItem(InventoryObject[indis_item].objectName , 1);

				drawing ="";
				yerlestirme = false;
				draw_apply = false;
				collision = false;
				current_cursor = "shoot";
			}
		else // eşya çizilmemişse
			{
					solid[indis_item].item_active = false;
					solid[indis_item].item_blendmode = "add";
					solid[indis_item].item_rect.x = (mouse.x/25)*25;
					solid[indis_item].item_rect.y = (mouse.y/12)*12;
					solid[indis_item].item_rect.w = 100;
					solid[indis_item].item_rect.h = 100;

					current_cursor = "sepia";

					if(cancel_draw)
					{
						solid[indis_item].item_name = "";
						solid[indis_item].item_blendmode = "";
						solid[indis_item].number_item = NULL;
						solid[indis_item].item_health = NULL;
						solid[indis_item].item_rect.x = NULL;
						solid[indis_item].item_rect.y = NULL;
						solid[indis_item].item_rect.w = NULL;
						solid[indis_item].item_rect.h = NULL;
						solid[indis_item].item_texture = NULL;

						drawing = "";
						draw_apply = false;
						yerlestirme = false;
						cancel_draw = false;
						collision = false;
						current_cursor = "shoot";

					}
			}
		}
	}
	
	
	if( SDL_HasIntersection(&solid_mouse , &rect_inventory))
	{
		for(int t=0;t<inventory_size;t++)
		{
			if((InventoryObject[t].xCoord <= x) && (InventoryObject[t].yCoord+50 >= x)) // mouse kutucuklardan birinin üzerindeyse
			{
				if(InventoryObject[t].objectName != "")
				{
					inf = "Bu nesneyi kullanmak icin sol tiklayin , silmek icin sag tiklayin";
					break;
				}
				else
				{
					inf = "";
				}
			}
			else
			{
				inf = "";
			}
		}
	}
	else
	{
		inf = "";
	}
	
	while((SDL_PollEvent(&tus) != 0)) // herhangi bir tuşa basılmışsa
	{
		switch(tus.type)
		{

			case SDL_QUIT :// sağ üstteki çarpıya basarsa
				exit(0); // oyundan çık
			break;
/////////////////////////////////////////////////////////// QUIT SONU ///////////////////////////////////////////////////////////////////////////////
			
			case SDL_MOUSEBUTTONDOWN:
				
				if((tus.button.button == SDL_BUTTON_LEFT) && (!SDL_HasIntersection(&solid_mouse , &rect_inventory)))
				{
						if(barbaros_guns == "knife" && drawing == "")
						{				
							barbaros_durum = "attack";
							//mevcut_mermi = "";
							
						}
						else if(barbaros_guns == "flash_light" && drawing == "")
						{

						}
						else if((barbaros_guns == "handgun" || barbaros_guns == "rifle" || barbaros_guns == "shotgun") && drawing == "")
						{

							if(barbaros_guns == "handgun")
							{
								mevcut_mermi = "handgun_mermi";

								if((handgun_mermi > 0))
								{
									if((barbaros_durum == "move"))
									{
										if(!active_bullet) // mermi çizimi yoksa
										{
											barbaros_durum = "attack";
											Mix_PlayChannel(2,minigun_shot,0);
											handgun_mermi = handgun_mermi - 1;
				
											active_bullet = true; // mermiyi çizmeye başla				
										}
									}// barbaros move sonu
								}// handgun < 0 sonu
							
								else // handgun mermi yoksa
								{
									handgun_mermi = 0;
									active_bullet = false;
								}
							}
							else if(barbaros_guns == "rifle")
							{
								mevcut_mermi ="rifle_mermi";
								if((rifle_mermi > 0))
								{
									if(barbaros_durum =="move")
									{
										if(!active_bullet)
										{
											barbaros_durum = "attack";
											Mix_PlayChannel(2,rifle_shot,0);
											rifle_mermi = rifle_mermi - 1;

											active_bullet = true;
										}
									}// barbaros durum onu
								} // rifle mermi sonu							

								else
								{
									rifle_mermi = 0;
									active_bullet = false;
								}
							}

							else if(barbaros_guns == "shotgun")
							{
								if((shotgun_mermi > 0))
								{
									if(barbaros_durum =="move")
									{
										if(!active_bullet)
										{
											barbaros_durum = "attack";
											Mix_PlayChannel(2 , shotgun_shot , 0);
											shotgun_mermi = shotgun_mermi - 1;
											
											active_bullet = true;
										}
									}
								}
								else
								{
									shotgun_mermi = 0;
									active_bullet = false;
								}
							}
							
						}
						
				}
				if((tus.button.button == SDL_BUTTON_LEFT) && health <= 0)
				{
					oyun_baslat = false;
				}
				
				if((tus.button.button == SDL_BUTTON_LEFT) && ( SDL_HasIntersection(&solid_mouse , &rect_inventory)) ) // envanterdeki herhangi bir nesneye sol tıklandığında
				{
					for(int t=0;t<inventory_size;t++)
					{
						if((InventoryObject[t].xCoord <= x) && (InventoryObject[t].yCoord+50 >= x)) // kutucuklardan birine tıklandıysa
						{
							if(InventoryObject[t].objectName == "health_bag")
							{
								
								health = health + 20;	
								
								if(health >= MAX_HEALTH)
									health = MAX_HEALTH;
								
								deleteItem(InventoryObject[t].objectName , 1);
								
							}

							if(InventoryObject[t].objectName == "handgun_mermi")
							{
								handgun_mermi = handgun_mermi + 10;
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "rifle_mermi")
							{
								rifle_mermi = rifle_mermi + 5;
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "shotgun_mermi")
							{
								shotgun_mermi = shotgun_mermi + 3;
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "rifle")
							{		
								mevcut_mermi = "rifle_mermi";
								barbaros_guns = "rifle";
							}

							if(InventoryObject[t].objectName == "handgun")
							{
								mevcut_mermi = "handgun_mermi";
								barbaros_guns = "handgun";
							}

							if(InventoryObject[t].objectName == "shotgun")
							{
								
								mevcut_mermi = "shotgun_mermi";
								barbaros_guns = "shotgun";
							}

							if(InventoryObject[t].objectName == "knife")
							{
							
								barbaros_guns = "knife";
								mevcut_mermi = "";
							}

							if(InventoryObject[t].objectName == "12_bag")
							{
								envanter_durum = "12_envanter";
								max_envanter = 12;
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "soup")
							{
								hunger = hunger + 25;
								thirtsy = thirtsy + 15;
								deleteItem(InventoryObject[t].objectName , 1);
								
							}

							if(InventoryObject[t].objectName == "water")
							{
								thirtsy = thirtsy + 40;
								Mix_PlayChannel(2 , water_drink , 0);
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "bread")
							{
								hunger = hunger + 40;
								Mix_PlayChannel(2 , food , 0);
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "full_bag")
							{
								envanter_durum = "full_envanter";
								max_envanter = 18;
								deleteItem(InventoryObject[t].objectName , 1);
							}

							if(InventoryObject[t].objectName == "energy_water")
							{
								thirtsy = thirtsy + 30;
								health = health + 20;
							
								deleteItem(InventoryObject[t].objectName , 1);
							}														
						} // envantere tıklama sonu
					} // for int t=0 sonu						
				} // sol tıklama sonu


				// nesneye sağ tıklandığında eşyayı siler sayısını 0 yapar
				else if ((tus.button.button == SDL_BUTTON_RIGHT) &&  SDL_HasIntersection(&solid_mouse , &rect_inventory)) // envanterdeki herhangi bir nesneye sağ tıklandığında
				{					
					for(int k=0;k<inventory_size;k++)
					{
						if(InventoryObject[k].objectName == "health_bag")
						{								
							InventoryObject[k].objectNumber = 0;						
							inventory_size--;
						}						
					}
				}
				else if (tus.button.button == SDL_BUTTON_LEFT)
				{
					move = true;
						if(drawing != "")
						{
							draw_apply = true;
							collision = false;
						}
						else
						{
							draw_apply = false;
							collision = false;
						}
				}

				else if ((tus.button.button == SDL_BUTTON_RIGHT))
				{
					cancel_draw = true;	
					move = true;
					x_target = mouse.x;
					y_target = mouse.y;

					playerAngle = angle;
				}

				break;
///////////////////////////////////////////// MOUSE BUTTON DOWN SONU /////////////////////////////////////////////////////////////////////////////////			
			case SDL_KEYDOWN:

			switch(tus.key.keysym.sym)
				{

					case SDLK_TAB: // oyunu durdurur	
					
						if(pause == false) // oyun devam ediyorsa
						{
							pause = true; // oyunu durdur
						}
						else // oyun durmuşsa
						{
							pause = false; // oyuna devam et
						}
						
					break;

					
					case SDLK_r:
						
						break;

					case SDLK_i: // its open inventory
						
						break;

					case SDLK_UP:
							
						break;

					case SDLK_DOWN:
							
						break;

						case SDLK_LEFT:
							
						break;

					case SDLK_RIGHT:
							
						break;
						
				} // switch sonu
			
			}		
		
	} // while sonu
	*/
	if(SDL_PollEvent(&mKey) == 0) // hiçbir tuşa basılmıyorsa
	{
		
	}
	
} // void Events :: klavye() sonu
