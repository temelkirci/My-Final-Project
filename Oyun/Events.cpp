#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include "Events.h"
#include <tuple>
#include <cmath>

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacaðýz

using namespace std;

Events::Events()
{
    current_cursor = "shoot";
	mevcut_resim = "sag";
	drawing = "";
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
	}
	else
	{
		current_cursor = "shoot";
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

	//cout<<angle<<endl;

	///// MOUSE A GÖRE HAREKET ////
	if(xpoz > x_target && move) 
	{
		xpoz = xpoz - speed;
		mevcut_resim = "sol";

		if(!Mix_Playing(1))
		{
			Mix_PlayChannel(1 , walk , 0);
		}
	}
	else if(xpoz+100 < x_target && move)
	{
		xpoz = xpoz + speed;
		mevcut_resim = "sag";


		if(!Mix_Playing(1))
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
	
			if(!Mix_Playing(1))
			{
				Mix_PlayChannel(1 , walk , 0);
			}
		}
		else if(ypoz+100 < y_target && move)
		{
			ypoz = ypoz + speed;
			mevcut_resim = "asagi";

			if(!Mix_Playing(1))
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

	if(drawing != "") // çizilecek eþya varsa
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
					break;
				}
			
			}
		}
		else // eþya bilgileri kaydedilmiþse
		{
			Solid_Items[indis_item].item_active = false;
			Solid_Items[indis_item].item_blendmode = "add";
			Solid_Items[indis_item].number_item = 1;
			
			for(int t=0;t<Collectible_Size;t++)
			{
				/*
				if((SDL_HasIntersection(&Solid_Items[indis_item].item_rect , &Solid_Items[t].item_rect)) && (t != indis_item))
				{
					collision = true;
					break;
				}
				*/
				//else 
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
		
			if(draw_apply) // eþyayý çiz
			{
				Solid_Items[indis_item].item_blendmode = "blend";
				Solid_Items[indis_item].item_active = true;
				Solid_Items[indis_item].item_health = 100;
				Solid_Items[indis_item].item_rect.x = (mouse.x/25)*25; 
				Solid_Items[indis_item].item_rect.y = (mouse.y/12)*12;   
				Solid_Items[indis_item].item_rect.w = 100;
				Solid_Items[indis_item].item_rect.h = 100;

				for(int i=0;i<inventory_size;i++)
				{
					if(get<0>(envanter[i]) == drawing)
					{
						indis_item = i;
						break;
					}
				}
				get<2>(envanter[indis_item]) = get<2>(envanter[indis_item]) - 1;
								
				if(get<2>(envanter[indis_item]) <= 0)
					inventory_size--;

				drawing ="";
				yerlestirme = false;
				draw_apply = false;
				collision = false;
				current_cursor = "shoot";
			}
		else // eþya çizilmemiþse
			{
					Solid_Items[indis_item].item_active = false;
					Solid_Items[indis_item].item_rect.x = (mouse.x/25)*25;
					Solid_Items[indis_item].item_rect.y = (mouse.y/12)*12;
					Solid_Items[indis_item].item_rect.w = 100;
					Solid_Items[indis_item].item_rect.h = 100;
					
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
						current_cursor = "sepia";
					}
			}
		}
	}

	
	for(int k=0;k<Collectible_Size;k++)
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
				if((get<3>(envanter[t]) <= x) && (get<3>(envanter[t])+50 >= x)) // mouse kutucuklardan birinin üzerindeyse
				{
					if(get<0>(envanter[t]) != "")
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
	
	while((SDL_PollEvent(&tus) != 0)) // herhangi bir tuþa basýlmýþsa
	{
		switch(tus.type)
		{

			case SDL_QUIT :// sað üstteki çarpýya basarsa
				exit(0); // oyundan çýk
			break;
/////////////////////////////////////////////////////////// QUIT SONU ///////////////////////////////////////////////////////////////////////////////
			
			case SDL_MOUSEBUTTONDOWN:
				
				if((tus.button.button == SDL_BUTTON_LEFT) && (!SDL_HasIntersection(&solid_mouse , &rect_inventory)))
				{
						if(barbaros_guns == "knife")
						{				
							barbaros_durum = "attack";
							//mevcut_mermi = "";
						}
						else if(barbaros_guns == "flash_light")
						{

						}
						else if(barbaros_guns == "handgun" || barbaros_guns == "rifle" || barbaros_guns == "shotgun")
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
											
											x_hedef = mouse.x;
											y_hedef = mouse.y;

											active_bullet = true; // mermiyi çizmeye baþla				
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
											//Mix_PlayChannel(2,rifle_shot,0);
											rifle_mermi = rifle_mermi - 1;

											x_hedef = mouse.x;
											y_hedef = mouse.y;
											
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
											
											x_hedef = mouse.x;	
											y_hedef = mouse.y;

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
				if((tus.button.button == SDL_BUTTON_LEFT) && ( SDL_HasIntersection(&solid_mouse , &rect_inventory)) ) // envanterdeki herhangi bir nesneye sol týklandýðýnda
				{
					for(int t=0;t<inventory_size;t++)
					{
						if((get<3>(envanter[t]) <= x) && (get<3>(envanter[t])+50 >= x)) // kutucuklardan birine týklandýysa
						{
							if(get<0>(envanter[t]) == "health_bag")
							{
								cout<<get<0>(envanter[t])<<endl;
								health = health + 20;	
								
								if(health >= MAX_HEALTH)
									health = MAX_HEALTH;
								
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
								
							}

							if(get<0>(envanter[t]) == "handgun_mermi")
							{
								handgun_mermi = handgun_mermi + 10;
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "rifle_mermi")
							{
								rifle_mermi = rifle_mermi + 5;
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "shotgun_mermi")
							{
								shotgun_mermi = shotgun_mermi + 3;
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "rifle")
							{		
								mevcut_mermi = "rifle_mermi";
								barbaros_guns = "rifle";
							}

							if(get<0>(envanter[t]) == "handgun")
							{
								mevcut_mermi = "handgun_mermi";
								barbaros_guns = "handgun";
							}

							if(get<0>(envanter[t]) == "shotgun")
							{
								cout<<get<0>(envanter[t])<<endl;
								mevcut_mermi = "shotgun_mermi";
								barbaros_guns = "shotgun";
							}

							if(get<0>(envanter[t]) == "12_bag")
							{
								envanter_durum = "12_envanter";
								max_envanter = 12;
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "full_bag")
							{
								envanter_durum = "full_envanter";
								max_envanter = 18;
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "energy_water")
							{
								thirtsy = thirtsy + 30;
								health = health + 20;
							
								get<2>(envanter[t]) = get<2>(envanter[t]) - 1;
								
								if(get<2>(envanter[t]) <= 0)
									inventory_size--;
							}

							if(get<0>(envanter[t]) == "rock_wall")
							{		
								drawing = "rock_wall";
								current_cursor = "sepia";
							}

							else if(get<0>(envanter[t]) == "stone_wall")
							{		
								drawing = "stone_wall";
								current_cursor = "sepia";
							}
						} // envantere týklama sonu
					} // for int t=0 sonu						
				} // sol týklama sonu

				else if ((!pause) && (tus.button.button == SDL_BUTTON_LEFT) &&  SDL_HasIntersection(&solid_mouse , &slot1_rect))
				{
					if(statu_crafting)
					{
						get<0>(Slot1) = "";
						get<1>(Slot1) = NULL;
						get<2>(Slot1) = false;
						get<3>(Slot1) = 0;
					}
				}

				else if ((!pause) && (tus.button.button == SDL_BUTTON_LEFT) &&  SDL_HasIntersection(&solid_mouse , &slot2_rect))
				{
					if(statu_crafting)
					{
						get<0>(Slot2) = "";
						get<1>(Slot2) = NULL;
						get<2>(Slot2) = false;
						get<3>(Slot2) = 0;
					}
				}

				else if ((!pause) && (tus.button.button == SDL_BUTTON_RIGHT) &&  SDL_HasIntersection(&solid_mouse , &final_rect))
				{
					if(statu_crafting)
					{
						
						if(get<2>(finalSlot))
						{
							Esya_Ekle(get<0>(finalSlot) , get<3>(finalSlot) , rend , get<1>(finalSlot)); // eþyanýn üzerine sað týklandýysa eþyayý envantere ekle
							for(int i=0;i<inventory_size;i++)
							{
								if((get<0>(Slot1) == get<0>(envanter[i]) ) || (get<0>(Slot2) == get<0>(envanter[i])))
								{
									get<2>(envanter[i]) = get<2>(envanter[i]) - 1;
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
				// nesneye sað týklandýðýnda eþyayý siler sayýsýný 0 yapar
				else if ((!pause) && (tus.button.button == SDL_BUTTON_RIGHT) &&  SDL_HasIntersection(&solid_mouse , &rect_inventory)) // envanterdeki herhangi bir nesneye sað týklandýðýnda
				{
	
					if(statu_crafting)
					{
						if(get<2>(Slot1) == false)
						{
							for(int k=0;k<inventory_size;k++)
							{
								if((get<3>(envanter[k]) <= x) && (get<3>(envanter[k])+50 >= x)) // kutucuklardan birine týklandýysa
								{
									get<0>(Slot1) = get<0>(envanter[k]);
									get<1>(Slot1) = get<1>(envanter[k]);
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
								if((get<3>(envanter[k]) <= x) && (get<3>(envanter[k])+50 >= x)) // kutucuklardan birine týklandýysa
								{
									get<0>(Slot2) = get<0>(envanter[k]);
									get<1>(Slot2) = get<1>(envanter[k]);
									get<2>(Slot2) = true;
									get<3>(Slot2) = 1;

									break;
								}
							}
						}
						
						
					}

					else // crafting penceresi açýk deðilse eþyayý sil (1 azalt)
					{
						for(int k=0;k<inventory_size;k++)
						{
							if(get<0>(envanter[k]) == "health_bag")
							{								
								get<2>(envanter[k]) = 0;						
								inventory_size--;
							}

						}
					}
				}
				else if ((!pause) && (tus.button.button == SDL_BUTTON_LEFT))
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

				else if ((!pause) && (tus.button.button == SDL_BUTTON_RIGHT))
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
						else // oyun durmuþsa
						{
							pause = false; // oyuna devam et
						}
						
					break;

					
					case SDLK_r:
						//health = 0;
						
						if(statu_crafting)
							statu_crafting = false;
						else
							statu_crafting = true;
						
						cout<<xpoz<<endl<<ypoz<<endl<<endl;
						break;

					case SDLK_t:
						trex_health = 0;
						trex_dead = true;
						break;
						
				} // switch sonu
			
			}		
		
	} // while sonu
	
	if(SDL_PollEvent(&tus) == 0) // hiçbir tuþa basýlmýyorsa
	{
		
	}
	
} // void Events :: klavye() sonu
