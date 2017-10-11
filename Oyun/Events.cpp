#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include "Events.h"
#include <tuple>
#include <cmath>

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacağız

using namespace std;

Events::Events()
{
    current_cursor = "shoot";
	mevcut_resim = "sag";
	drawing = "";

	xtank = 1000;
	ytank = 200;

	player_inf = false;
	draw_apply = false;
	yerlestirme = false;
	cancel_draw = false;
	collision = false;

	xpoz = 625;
	ypoz = 300;
	
	arti_y_speed = speed;
    arti_x_speed = speed;
    eksi_y_speed = speed;
    eksi_x_speed = speed;

	pause = false;
	move = false;
}

Events::~Events()
{
	
}

void Events :: klavye(SDL_Renderer* rend , int camx , int camy)
{
	tus;
	int x , y;	

	SDL_GetMouseState(&x,&y);

	solid_mouse.x=x;
	solid_mouse.y=y;
	solid_mouse.w=30;
	solid_mouse.h=30;

	mouse.x=x-camx;
	mouse.y=y-camy;
	mouse.w=30;
	mouse.h=30;

	
	if(SDL_HasIntersection(&solid_mouse , &rect_inventory)) // mouse envanterin üzerineyse ok imleci gözüksün
	{
		current_cursor = "sepia";

		for(int t=0;t<inventory_size;t++)
		{
			if((InventoryObject[t].xCoord <= x) && (InventoryObject[t].xCoord+50 >= x)) // kutucukların üzerindeyse
			{			
				infItem = InventoryObject[t].objectName;
				break;
			}
			infItem = "";
		}
		
	}
	else
	{	
		current_cursor = "shoot";
		infItem = "";	
	}
	
	
	if((xpoz+50) <= mouse.x) // mouse sað tarafta ise
	{
		if((ypoz+50) <= mouse.y) // 1.bölge (sað-alt)
		{
			 x_distance = abs(mouse.x - (xpoz + 50));
			 y_distance = abs(mouse.y - (ypoz + 50));

			if(x_distance == 0)
				x_distance = 1;
			if(y_distance == 0)
				y_distance = 1;

			tanjant = y_distance / x_distance ;
			tanjant_angle = (atan(tanjant) * 180) / PI ;
			angle = tanjant_angle ;

		}

		else // 4.bölge (sað-üst)
		{
			x_distance = abs(mouse.x - (xpoz + 50));
			y_distance = abs(mouse.y - (ypoz + 50));

			if(x_distance == 0)
				x_distance = 1;
			if(y_distance == 0)
				y_distance = 1;

			tanjant = y_distance / x_distance ;
			tanjant_angle = (atan(tanjant) * 180) / PI ; // atan fonksiyonu ile y_distance / x_distance oranýna göre x eksenine göre açýyý hesaplýyoruz
			angle = 360 - tanjant_angle ; 
		
		}
	}

	else // mouse sol tarafta ise
	{
		if(ypoz+50 <= mouse.y) // 2.bölge (sol-alt)
		{
			x_distance = abs((xpoz + 50) - mouse.x);
			y_distance = abs(mouse.y - (ypoz + 50));

			if(x_distance == 0)
				x_distance = 1;
			if(y_distance == 0)
				y_distance = 1;

			tanjant = y_distance / x_distance ;
			tanjant_angle = (atan(tanjant) * 180) / PI ; // atan fonksiyonu ile y_distance / x_distance oranýna göre x eksenine göre açýyý hesaplýyoruz
			angle = 180 - tanjant_angle ;	

		}

		else // 3.bölge (sol-üst)
		{
			x_distance = abs((xpoz + 50) - mouse.x);
			y_distance = abs(mouse.y - (ypoz + 50));

			if(x_distance == 0)
				x_distance = 1;
			if(y_distance == 0)
				y_distance = 1;

			tanjant = y_distance / x_distance ;
			tanjant_angle = (atan(tanjant) * 180) / PI ;
			angle = 180 + tanjant_angle ;	

		}
	}


	///// MOUSE A GÖRE HAREKET ////
	if(xpoz > x_target && move) 
	{
		xpoz = xpoz - speed;
		mevcut_resim = "sol";
		
		if(!Mix_Playing(1) && speed != 0)
		{
			Mix_PlayChannel(1 , walk , 0);
		}
	}
	else if(xpoz+50 < x_target && move)
	{
		xpoz = xpoz + speed;
		mevcut_resim = "sag";

		if(!Mix_Playing(1) && speed != 0)
		{
			Mix_PlayChannel(1 , walk , 0);
		}
	}
	else
	{
		if(ypoz > y_target && move)
		{
			ypoz = ypoz - speed;
			mevcut_resim = "yukari";

			if(!Mix_Playing(1) && speed != 0)
			{
				Mix_PlayChannel(1 , walk , 0);
			}
		}
		else if(ypoz+50 < y_target && move)
		{
			ypoz = ypoz + speed;
			mevcut_resim = "asagi";
		
			if(!Mix_Playing(1) && speed != 0)
			{
				Mix_PlayChannel(1 , walk , 0);
			}
		}
		else
		{
			move=false; // dont move
		}

	}
	////////////////////////

	if(drawing != "") // çizilecek eşya varsa
	{
		current_cursor = "sepia";
		if(!yerlestirme)
		{
			for(int j=0;j<Collectible_Size;j++)
			{
				if((Solid_Items[j].item_name == "")) // çizilecek item için indis bulma
				{
					Solid_Items[j].item_name = drawing;
					Solid_Items[j].item_id = j;
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
			Solid_Items[indis_item].item_active = false;
			Solid_Items[indis_item].item_blendmode = "add";
			Solid_Items[indis_item].number_item = 1;

				if(Solid_Items[indis_item].item_name == "wood_block")
					Solid_Items[indis_item].item_health = 1000;
				if(Solid_Items[indis_item].item_name == "brick_block")
					Solid_Items[indis_item].item_health = 2000;
				if(Solid_Items[indis_item].item_name == "stone_block")
					Solid_Items[indis_item].item_health = 3000;
				if(Solid_Items[indis_item].item_name == "iron_block")
					Solid_Items[indis_item].item_health = 4000;
				if(Solid_Items[indis_item].item_name == "steel_block")
					Solid_Items[indis_item].item_health = 5000;
				

			for(int t=0;t<Collectible_Size;t++)
			{
				
				if((SDL_HasIntersection(&Solid_Items[indis_item].item_rect , &Uncollectible_Items[t].item_rect)))
				{
					collision = true;
					break;
				}
				else if((SDL_HasIntersection(&Solid_Items[indis_item].item_rect , &Collectible_Items[t].item_rect)))
				{
					collision = true;
					break;
				}
				else if((SDL_HasIntersection(&Solid_Items[indis_item].item_rect , &player_barbaros)))
				{
					collision = true;
					break;
				}
				
			}
			
			
			if(collision == true)
				draw_apply = false;
		
			if(draw_apply) // eşyayı çiz
			{
				Solid_Items[indis_item].item_blendmode = "blend";
				Solid_Items[indis_item].item_active = true;
				Solid_Items[indis_item].item_rect.x = (mouse.x/25)*25; 
				Solid_Items[indis_item].item_rect.y = (mouse.y/12)*12;   
				Solid_Items[indis_item].item_rect.w = 100;
				Solid_Items[indis_item].item_rect.h = 100;
				
				if(Solid_Items[indis_item].item_blendmode == "wood_block")
					Solid_Items[indis_item].item_health = 1000;
				if(Solid_Items[indis_item].item_blendmode == "brick_block")
					Solid_Items[indis_item].item_health = 2000;
				if(Solid_Items[indis_item].item_blendmode == "stone_block")
					Solid_Items[indis_item].item_health = 3000;
				if(Solid_Items[indis_item].item_blendmode == "iron_block")
					Solid_Items[indis_item].item_health = 4000;
				if(Solid_Items[indis_item].item_blendmode == "steel_block")
					Solid_Items[indis_item].item_health = 5000;
				

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
					Solid_Items[indis_item].item_active = false;
					Solid_Items[indis_item].item_blendmode = "add";
					Solid_Items[indis_item].item_rect.x = (mouse.x/25)*25;
					Solid_Items[indis_item].item_rect.y = (mouse.y/12)*12;
					Solid_Items[indis_item].item_rect.w = 100;
					Solid_Items[indis_item].item_rect.h = 100;

					current_cursor = "sepia";

					if(cancel_draw)
					{
						Solid_Items[indis_item].item_name = "";
						Solid_Items[indis_item].item_blendmode = "";
						Solid_Items[indis_item].item_id = NULL;
						Solid_Items[indis_item].number_item = NULL;
						Solid_Items[indis_item].item_health = NULL;
						Solid_Items[indis_item].item_rect.x = NULL;
						Solid_Items[indis_item].item_rect.y = NULL;
						Solid_Items[indis_item].item_rect.w = NULL;
						Solid_Items[indis_item].item_rect.h = NULL;
						Solid_Items[indis_item].item_texture = NULL;

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

	

	for(int k=0;k<10;k++)
	{
		if(SDL_HasIntersection(&mouse , &Collectible_Items[k].item_rect))
		{
			inf = Collectible_Items[k].item_name;
			break;
		}
		if(SDL_HasIntersection(&mouse , &(Uncollectible_Items[k].item_rect )))
		{
			inf = Uncollectible_Items[k].item_name;
			break;
		}
		if(SDL_HasIntersection(&mouse , &Solid_Items[k].item_rect))
		{
			inf = Solid_Items[k].item_name;
			break;
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
						else // tank
						{

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

						
							if(InventoryObject[t].objectName == "stone_block")
							{		
								drawing = "stone_block";
								current_cursor = "sepia";
								yerlestirme = false;
							}

							else if(InventoryObject[t].objectName == "brick_block")
							{		
								drawing = "brick_block";
								current_cursor = "sepia";
								yerlestirme = false;
							}

							else if(InventoryObject[t].objectName == "iron_block")
							{		
								drawing = "iron_block";
								current_cursor = "sepia";
								yerlestirme = false;
							}

							else if(InventoryObject[t].objectName == "steel_block")
							{		
								drawing = "steel_block";
								current_cursor = "sepia";
								yerlestirme = false;
							}

							else if(InventoryObject[t].objectName == "box_block")
							{		
								drawing = "box_block";
								current_cursor = "sepia";
								yerlestirme = false;
							}
							
						} // envantere tıklama sonu
					} // for int t=0 sonu						
				} // sol tıklama sonu

				else if ((tus.button.button == SDL_BUTTON_LEFT) &&  SDL_HasIntersection(&solid_mouse , &slot1_rect))
				{
					if(statu_crafting)
					{
						get<0>(Slot1) = "";
						get<1>(Slot1) = NULL;
						get<2>(Slot1) = false;
						get<3>(Slot1) = 0;
					}
				}

				else if ((tus.button.button == SDL_BUTTON_LEFT) &&  SDL_HasIntersection(&solid_mouse , &slot2_rect))
				{
					if(statu_crafting)
					{
						get<0>(Slot2) = "";
						get<1>(Slot2) = NULL;
						get<2>(Slot2) = false;
						get<3>(Slot2) = 0;
					}
				}

				else if ((tus.button.button == SDL_BUTTON_RIGHT) &&  SDL_HasIntersection(&solid_mouse , &final_rect))
				{
					if(statu_crafting)
					{
						
						if(get<2>(finalSlot))
						{
							Esya_Ekle(get<0>(finalSlot) , get<3>(finalSlot) , rend , get<1>(finalSlot)); // eşyanın üzerine sağ tıklandıysa eşyayı envantere ekle
							for(int i=0;i<inventory_size;i++)
							{
								if((get<0>(Slot1) == InventoryObject[i].objectName) || (get<0>(Slot2) == InventoryObject[i].objectName))
								{
									InventoryObject[i].objectNumber = InventoryObject[i].objectNumber - 1;
									break;
								}
							}
								get<0>(Slot1) = "";
								get<1>(Slot1) = NULL;
								get<2>(Slot1) = false;
								get<3>(Slot1) = 0;

								get<0>(Slot2) = "";
								get<1>(Slot2) = NULL;
								get<2>(Slot2) = false;
								get<3>(Slot2) = 0;

								get<0>(finalSlot) = "";
								get<1>(finalSlot) = NULL;
								get<2>(finalSlot) = false;
								get<3>(finalSlot) = 0;
						}
					}
				}
				// nesneye sağ tıklandığında eşyayı siler sayısını 0 yapar
				else if ((tus.button.button == SDL_BUTTON_RIGHT) &&  SDL_HasIntersection(&solid_mouse , &rect_inventory)) // envanterdeki herhangi bir nesneye sağ tıklandığında
				{
	
					if(statu_crafting)
					{
						if(get<2>(Slot1) == false)
						{
							for(int k=0;k<inventory_size;k++)
							{
								if((InventoryObject[k].objectNumber <= x) && (InventoryObject[k].objectNumber+50 >= x)) // kutucuklardan birine tıklandıysa
								{
									get<0>(Slot1) = InventoryObject[k].objectName;
									get<1>(Slot1) = InventoryObject[k].objectTexture;
									get<2>(Slot1) = true;
									get<3>(Slot1) = 1;
									
									break;
								}
							}
						}
						else if (get<2>(Slot2) == false)
						{
							for(int k=0;k<inventory_size;k++)
							{
								if((InventoryObject[k].xCoord <= x) && (InventoryObject[k].yCoord+50 >= x)) // kutucuklardan birine tıklandıysa
								{
									get<0>(Slot2) = InventoryObject[k].objectName;
									get<1>(Slot2) = InventoryObject[k].objectTexture;
									get<2>(Slot2) = true;
									get<3>(Slot2) = 1;

									break;
								}
							}
						}
						
						
					}

					else // crafting penceresi açık değilse eşyayı sil (1 azalt)
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
						
						if(statu_crafting)
							statu_crafting = false;
						else
							statu_crafting = true;
						
						break;

					case SDLK_t:
						
						if(InventoryStore.OpenInventory)
							InventoryStore.OpenInventory = false;
						else
							InventoryStore.OpenInventory = true;
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
	
	if(SDL_PollEvent(&tus) == 0) // hiçbir tuşa basılmıyorsa
	{
		
	}
	
} // void Events :: klavye() sonu
