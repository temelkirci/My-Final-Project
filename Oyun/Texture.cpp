#include <iostream>
#include "Texture.h"
#include <string>
#include <SDL/SDL.h>

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacağız

Texture :: Texture()
{
	object_collision = false;

	map_column = 6;
	map_row = 5;

	map.x = -300;
	map.y = 0;
	map.w = 300;
	map.h = 200;

	map_x = -300;
	map_y = 0;

	camera.x = 0;
	camera.y = 0;
	camera.w = 6000;
	camera.h = 3000;
}

Texture :: ~Texture()
{
	SDL_FreeSurface(load_surface);
	SDL_DestroyTexture(load_texture);
	SDL_FreeSurface(surface_background);
	SDL_DestroyTexture(texture_background);
	
	load_surface = NULL;
	load_texture = NULL ;
	surface_background = NULL ;
	texture_background = NULL ;
}


bool Texture :: load(char* dosya_adi , string texture_adi , SDL_Renderer* texture_render)
{
	load_surface = IMG_Load(dosya_adi);
	
	if(load_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Texture" , "Texture :: load (load_surface yuklenemedi..!)" , NULL);
		cout<<texture_adi<<endl;
		//exit(0);
	}

	load_texture = SDL_CreateTextureFromSurface(texture_render , load_surface);	// yüzeyi renderleyerek texture oluştur	
	SDL_FreeSurface(load_surface);
	if(load_texture != 0)
	{
		map_texture[texture_adi] = load_texture; // Tüm textureleri saklayacağımız yer
		all_textures[texture_adi] = load_texture;
		return true;
	}
	return false;
}

void Texture :: draw_camera(SDL_Renderer* ren , int* pozx, int* pozy, int genislik , int yukseklik)
{
	// barbaros genislik 100
			// barbaros yukseklik 100
			// ekran yukseklik 700
			// ekran genislik 1350
			// arkaplan genislik 6000
			// arkaplan yukseklik 3000
			
			if((*pozy) < 300)
			{
				camera.y = 0;
			}

			if((*pozx) < 625)
			{
				camera.x = 0;
			}

			if((*pozy) >= 1100)
			{
				camera.y = -800;
				if((*pozy) >= 1400)
					(*pozy) = 1400;
			}

			if((((*pozy) >= 300) && ((*pozy) < 1100)))
			{
				camera.y = -((*pozy) - 300);
			}

			if((*pozx) >= 5275)
			{
				camera.x = -4650;
			}

			if((*pozx) >= 5900) // haritanýn en saðýndan çýkmamasý için kontrol yapýlýyor
			{
				(*pozx) = 5900;
			}

			if(((625 <= (*pozx)) && ((*pozx) < 5275)))
			{
				camera.x = -((*pozx) - 625);
			}
			
			//SDL_RenderCopyEx(ren, texture_background , NULL , &camera , 0 , 0 , SDL_FLIP_NONE);
	
	
	if(camera.x >= 0 && camera.x <= 625)
	{
		map_x = -300;
	}
	else
	{
		map_x = ((-camera.x) / 300 - 1) * 300;
	}
	
	if(camera.y >= 0 && camera.y <= 300)
	{
		map_y = 0;
	}
	else
	{
		map_y = ((-camera.y) / 200 ) * 200;
	}
	
	//SDL_RenderSetClipRect(ren , &map);

	for(int i=0;i<map_row;i++) // satır = 5
	{
		for(int j=0;j<map_column;j++) // sütun = 6
		{
			map_x = map_x + map.w;
			
			map.x = map_x + camera.x;
			map.y = map_y + camera.y;

			SDL_RenderCopyEx(ren, texture_background , NULL , &map , 0 , 0 , SDL_FLIP_NONE);
		}
		map_x = ((-camera.x) / 300 - 1) * 300;
		map_y = map_y + map.h;
	}
	map_x = ((-camera.x) / 300 - 1) * 300;
	map_y = ((-camera.y) / 200 ) * 200 ;
	
	
}

void Texture :: item_bilgi(SDL_Renderer* ren , string inf_text)
{
	Write(ren , 0 , inf_text , 3000);
}

void Texture :: draw_object(SDL_Renderer* texture_render , Uint32 collectible_time) 
{
	SDL_Rect hedef_texture;
	SDL_Rect temp;

	SDL_Rect barbaros_rect;
			barbaros_rect.x = xpoz;
			barbaros_rect.y = ypoz;
			barbaros_rect.w = 100;
			barbaros_rect.h = 100;


	for(int i=0;i<Collectible_Size;i++)
	{
		temp = Collectible_Items[i].item_rect;

		if((Collectible_Items[i].item_name != "" ) && (Collectible_Items[i].number_item > 0)) // obje çizilecekse
		{

			hedef_texture.x=Collectible_Items[i].item_rect.x + camera.x;
			hedef_texture.y=Collectible_Items[i].item_rect.y + camera.y;
			hedef_texture.w=Collectible_Items[i].item_rect.w;
			hedef_texture.h=Collectible_Items[i].item_rect.h;
			
			for(int t=0;t<Collectible_Size;t++)
			{
				
				if((SDL_HasIntersection(&temp , &Solid_Items[t].item_rect)) && (Solid_Items[t].item_active == true))
				{
					object_collision = true;
					break;
				}
				
				else if((SDL_HasIntersection(&temp , &Uncollectible_Items[t].item_rect)))
				{
					if((Uncollectible_Items[t].item_name == "bullet_handgun") || (Uncollectible_Items[t].item_name == "bullet_rifle") || (Uncollectible_Items[t].item_name == "bullet_shotgun"))
					{
						object_collision = false;
						break;
					}
					else
					{
						object_collision = true;
						break;
					}
				}
				
				else if((SDL_HasIntersection(&temp , &Collectible_Items[t].item_rect)) && (i != t))
				{
					object_collision = true;
					break;
				}
				
				else
				{
					object_collision = false;
					
				}
				
			}
			
			if(object_collision) // çizilecek nesne çakışıyorsa çizme yeni bir koordinat bul
			{
					
				Collectible_Items[i].item_rect.x=rand()%6000;
				Collectible_Items[i].item_rect.y=rand()%1500;
			}
			else // çizilecek nesne çakışmıyorsa nesneyi çiz 
			{
				SDL_RenderCopyEx(texture_render , map_texture[Collectible_Items[i].item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
			
				if(SDL_HasIntersection(&temp , &barbaros_rect) && (inventory_size < max_envanter)) // barbaros eşyaya temas ettiyse
				{
					Esya_Ekle(Collectible_Items[i].item_name , 1 , texture_render , map_texture[Collectible_Items[i].item_name]);

					if((Collectible_Items[i].item_name == "handgun") || (Collectible_Items[i].item_name == "shotgun") || (Collectible_Items[i].item_name == "rifle") || (Collectible_Items[i].item_name == "knife"))
					{
						Collectible_Items[i].item_name = "";
						Collectible_Items[i].item_blendmode = "";
						Collectible_Items[i].item_id = NULL;
						Collectible_Items[i].number_item = NULL;
						Collectible_Items[i].item_health = NULL;
						Collectible_Items[i].item_rect.x = NULL;
						Collectible_Items[i].item_rect.y = NULL;
						Collectible_Items[i].item_rect.w = NULL;
						Collectible_Items[i].item_rect.h = NULL;
						Collectible_Items[i].item_texture = NULL;
					}
					else
					{
						Collectible_Items[i].item_rect.x=rand()%6000;
						Collectible_Items[i].item_rect.y=rand()%1500;
					}
				}
				else if((inventory_size >= max_envanter) && (SDL_HasIntersection(&temp , &barbaros_rect)))
				{
					Write(texture_render , collectible_time , "Envanter Full" , -1);
				}
			}
		}
	} // en dıştaki for
}
	
// İçinden geçilemeyen , toplanamaz nesneleri çizer
// dağlar 

void Texture :: draw_solid_texture(SDL_Renderer* texture_render) 
{
	
	SDL_Rect hedef_texture;

	for(int t=0;t<Solid_Size;t++)
		{
			if(((Solid_Items[t].item_name) != "") && (Solid_Items[t].item_health > 0)) // nesne çizilecek
			{
				hedef_texture.x=Solid_Items[t].item_rect.x + camera.x;
				hedef_texture.y=Solid_Items[t].item_rect.y + camera.y;
				hedef_texture.w=Solid_Items[t].item_rect.w;
				hedef_texture.h=Solid_Items[t].item_rect.h;
				
				if(Solid_Items[t].item_blendmode == "add")
					SDL_SetTextureBlendMode(map_texture[Solid_Items[t].item_name] , SDL_BLENDMODE_ADD);
				else if(Solid_Items[t].item_blendmode == "blend")
					SDL_SetTextureBlendMode(map_texture[Solid_Items[t].item_name] , SDL_BLENDMODE_BLEND);
					
				SDL_RenderCopyEx(texture_render , map_texture[Solid_Items[t].item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
				
				SDL_Rect barbaros_rect;
				barbaros_rect.x = xpoz;
				barbaros_rect.y = ypoz;
				barbaros_rect.w = 100;
				barbaros_rect.h = 100;

				SDL_Rect temp = Solid_Items[t].item_rect;
			
				if((Solid_Items[t].item_active) == true)
				{
							if( (SDL_HasIntersection(&barbaros_rect , &temp)) && ((mevcut_resim == "yukari" )))
							{
								ypoz = (temp.y + temp.h);
							}

							if((SDL_HasIntersection(&barbaros_rect , &temp)) && ((mevcut_resim =="asagi" )))
							{
								ypoz = (temp.y - barbaros_rect.h);
							}

							if( (SDL_HasIntersection(&barbaros_rect , &temp)) && ( (mevcut_resim =="sag" )))
							{
								xpoz = (temp.x - barbaros_rect.w);
							}

							if((SDL_HasIntersection(&barbaros_rect , &temp)) && ((mevcut_resim =="sol" )))
							{
								xpoz = (temp.x + temp.w);			
							}
				}
					
			}
		}								
}
// İçinden geçilebilen , toplanamaz nesneleri çizer
// yer şekilleri , göl 
void Texture :: draw_texture(SDL_Renderer* texture_render) 
{
	
	for(int i=0;i<Collectible_Size;i++)
	{
		if(Uncollectible_Items[i].item_name != "" && Uncollectible_Items[i].item_active == true)
		{
			SDL_Rect hedef_texture;
				hedef_texture.x=Uncollectible_Items[i].item_rect.x + camera.x;
				hedef_texture.y=Uncollectible_Items[i].item_rect.y + camera.y;
				hedef_texture.w=Uncollectible_Items[i].item_rect.w;
				hedef_texture.h=Uncollectible_Items[i].item_rect.h;
	
			SDL_Rect barbaros_rect;
				barbaros_rect.x = xpoz;
				barbaros_rect.y = ypoz;
				barbaros_rect.w = 100;
				barbaros_rect.h = 100;

			if(Uncollectible_Items[i].item_name == "bullet_rifle" || Uncollectible_Items[i].item_name == "bullet_handgun" || Uncollectible_Items[i].item_name == "bullet_shotgun")
			{
				if((SDL_HasIntersection(&creature_rect , &Uncollectible_Items[i].item_rect)))
				{
					creature_health -=20;
					z = 0;
					Uncollectible_Items[i].item_active = false;
				}
				if(Uncollectible_Items[i].item_active)
					SDL_RenderCopyEx(texture_render , map_texture[Uncollectible_Items[i].item_name] , NULL , &hedef_texture , bullet_angle , 0 , SDL_FLIP_NONE);
				
			}
			else
			{
				// SDL_BLENDMODE_NONE : nesneyi görünmez yapar ve çizer
				// SDL_BLENDMODE_BLEND : nesneyi normal çizer
				// SDL_BLENDMODE_ADD : nesneyi parlak çizer

				SDL_RenderCopyEx(texture_render , map_texture[Uncollectible_Items[i].item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
			}
		}
	}
}

void Texture :: arkaplan_yükle(char* dosya_yolu , SDL_Renderer* render_arkaplan)
{
	surface_background = IMG_Load(dosya_yolu);
	if(surface_background == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Texture" , "arkaplan yuklenemedi..!" , NULL);
		exit(0);
	}
	texture_background = SDL_CreateTextureFromSurface(render_arkaplan , surface_background);
	SDL_FreeSurface(surface_background);
}

void Texture :: draw_bullet(SDL_Renderer* rend)
{
	if(active_bullet)
	{
		if(z >= 0 && z < 50)
		{		
			if(barbaros_guns == "rifle")
			{
				if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							Uncollectible_Items[9].item_rect.x = xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							Uncollectible_Items[9].item_rect.y = ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							Uncollectible_Items[9].item_rect.x = xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							Uncollectible_Items[9].item_rect.y = ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							Uncollectible_Items[9].item_rect.x = xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							Uncollectible_Items[9].item_rect.y = ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							Uncollectible_Items[9].item_rect.x = xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							Uncollectible_Items[9].item_rect.y = ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						Uncollectible_Items[9].item_rect.w = 20;
						Uncollectible_Items[9].item_rect.h = 5;
						Uncollectible_Items[9].item_active = true;
						Uncollectible_Items[9].item_name = "bullet_rifle";
						
					}

					if(bullet_angle == 270)
					{
						Uncollectible_Items[9].item_rect.y = (Uncollectible_Items[9].item_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						Uncollectible_Items[9].item_rect.x = (Uncollectible_Items[9].item_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						Uncollectible_Items[9].item_rect.y = (Uncollectible_Items[9].item_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						Uncollectible_Items[9].item_rect.x = (Uncollectible_Items[9].item_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						Uncollectible_Items[9].item_rect.y = (Uncollectible_Items[9].item_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						Uncollectible_Items[9].item_rect.x = (Uncollectible_Items[9].item_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						Uncollectible_Items[9].item_rect.y = (Uncollectible_Items[9].item_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						Uncollectible_Items[9].item_rect.x = (Uncollectible_Items[9].item_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						Uncollectible_Items[9].item_rect.y = (Uncollectible_Items[9].item_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}
					
					draw_texture(rend);
					z++;		
			
				}
				else if(barbaros_guns == "handgun")
				{
					if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							Uncollectible_Items[8].item_rect.x = xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							Uncollectible_Items[8].item_rect.y = ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							Uncollectible_Items[8].item_rect.x = xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							Uncollectible_Items[8].item_rect.y = ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							Uncollectible_Items[8].item_rect.x = xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							Uncollectible_Items[8].item_rect.y = ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							Uncollectible_Items[8].item_rect.x = xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							Uncollectible_Items[8].item_rect.y = ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						Uncollectible_Items[8].item_rect.w = 20;
						Uncollectible_Items[8].item_rect.h = 5;
						Uncollectible_Items[8].item_active = true;
						Uncollectible_Items[8].item_name = "bullet_handgun";
						
					}
					if(bullet_angle == 270)
					{
						Uncollectible_Items[8].item_rect.y = (Uncollectible_Items[8].item_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						Uncollectible_Items[8].item_rect.x = (Uncollectible_Items[8].item_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						Uncollectible_Items[8].item_rect.y = (Uncollectible_Items[8].item_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						Uncollectible_Items[8].item_rect.x = (Uncollectible_Items[8].item_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						Uncollectible_Items[8].item_rect.y = (Uncollectible_Items[8].item_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						Uncollectible_Items[8].item_rect.x = (Uncollectible_Items[8].item_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						Uncollectible_Items[8].item_rect.y = (Uncollectible_Items[8].item_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						Uncollectible_Items[8].item_rect.x = (Uncollectible_Items[8].item_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						Uncollectible_Items[8].item_rect.y = (Uncollectible_Items[8].item_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}
					
					draw_texture(rend);
					z++;	
					
				}
				else if(barbaros_guns == "shotgun")
				{
					if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							Uncollectible_Items[7].item_rect.x = xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							Uncollectible_Items[7].item_rect.y = ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							Uncollectible_Items[7].item_rect.x = xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							Uncollectible_Items[7].item_rect.y = ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							Uncollectible_Items[7].item_rect.x = xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							Uncollectible_Items[7].item_rect.y = ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							Uncollectible_Items[7].item_rect.x = xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							Uncollectible_Items[7].item_rect.y = ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						Uncollectible_Items[7].item_rect.w = 20;
						Uncollectible_Items[7].item_rect.h = 5;
						Uncollectible_Items[7].item_active = true;
						Uncollectible_Items[7].item_name = "bullet_shotgun";
						
					}
					if(bullet_angle == 270)
					{
						Uncollectible_Items[7].item_rect.y = (Uncollectible_Items[7].item_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						Uncollectible_Items[7].item_rect.x = (Uncollectible_Items[7].item_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						Uncollectible_Items[7].item_rect.y = (Uncollectible_Items[7].item_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						Uncollectible_Items[7].item_rect.x = (Uncollectible_Items[7].item_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						Uncollectible_Items[7].item_rect.y = (Uncollectible_Items[7].item_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						Uncollectible_Items[7].item_rect.x = (Uncollectible_Items[7].item_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						Uncollectible_Items[7].item_rect.y = (Uncollectible_Items[7].item_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						Uncollectible_Items[7].item_rect.x = (Uncollectible_Items[7].item_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						Uncollectible_Items[7].item_rect.y = (Uncollectible_Items[7].item_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}
					
					draw_texture(rend);
					z++;	
				}
					
		}

		if(z >= 50) // menzili aştıysa çizmeyi bırak
		{
			z=0;
			active_bullet = false;
			barbaros_durum = "move";
			Uncollectible_Items[7].item_active = false;
			Uncollectible_Items[8].item_active = false;
			Uncollectible_Items[9].item_active = false;	
		}
	}
}

void Texture :: load_textures(SDL_Renderer* renderer)
{	
	load("assets/guns/health_bag.png", "health_bag", renderer);
	load("assets/guns/full_bag.png", "full_bag", renderer);
	load("assets/guns/12_bag.png", "12_bag", renderer);
	load("assets/guns/handgun_mermi.png", "handgun_mermi", renderer);
	load("assets/guns/shotgun_mermi.png", "shotgun_mermi", renderer);
	load("assets/guns/rifle_mermi.png", "rifle_mermi", renderer);
	load("assets/guns/rifle.png", "rifle", renderer);
	load("assets/guns/shotgun.png", "shotgun", renderer);
	load("assets/guns/handgun.png", "handgun", renderer);		
	load("assets/guns/knife.png", "knife", renderer);

	load("assets/cursor.png", "shoot", renderer);
	load("assets/Sepia.png", "sepia", renderer);
	load("assets/guns/soup.png", "soup", renderer);
	load("assets/huge_box.jpg", "huge_box", renderer);
	load("assets/guns/rifle.png", "rifle", renderer);

	arkaplan_yükle("assets/desertt.jpg", renderer);
	load("assets/guns/bullet_handgun.png", "bullet_handgun", renderer);
	load("assets/guns/bullet_shotgun.png", "bullet_shotgun", renderer);
	load("assets/guns/bullet_rifle.png", "bullet_rifle", renderer);
}