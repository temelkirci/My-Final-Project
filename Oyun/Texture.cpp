#include <iostream>
#include "Texture.h"
#include <string>
#include <SDL/SDL.h>

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacaðýz

Texture :: Texture()
{
	object_collision = false;
	
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


bool Texture :: load(string dosya_adi , string texture_adi , SDL_Renderer* texture_render)
{
	load_surface = IMG_Load(dosya_adi.c_str());
	
	if(load_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Texture" , "Texture :: load (load_surface yuklenemedi..!)" , NULL);
		cout<<texture_adi<<endl;
		//exit(0);
	}

	load_texture = SDL_CreateTextureFromSurface(texture_render , load_surface);	// yüzeyi renderleyerek texture oluþtur	
	SDL_FreeSurface(load_surface);
	if(load_texture != 0)
	{
		map_texture[texture_adi] = load_texture; // Tüm textureleri saklayacaðýmýz yer
		all_textures[texture_adi] = load_texture;
		return true;
	}
	return false;
}

void Texture :: item_bilgi(SDL_Renderer* ren , string inf_text)
{
	Write(ren , 0 , inf_text);
}

// toplanýlabilir , içinden geçilebilir nesneleri çizer
// silahlar , yiyecekler , içecekler , mermi , çanta
void Texture :: draw_object(SDL_Renderer* texture_render) 
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
			
			if(object_collision) // çizilecek nesne çakýþýyorsa çizme yeni bir koordinat bul
			{
					
				Collectible_Items[i].item_rect.x=rand()%800;
				Collectible_Items[i].item_rect.y=rand()%800;
			}
			else // çizilecek nesne çakýþmýyorsa nesneyi çiz 
			{
				SDL_RenderCopyEx(texture_render , map_texture[Collectible_Items[i].item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
			
				if(SDL_HasIntersection(&temp , &barbaros_rect)) // barbaros eþyaya temas ettiyse
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
						Collectible_Items[i].item_rect.x=rand()%800;
						Collectible_Items[i].item_rect.y=rand()%800;
					}
				}
			}
		}
	} // en dýþtaki for
}
	
// Ýçinden geçilemeyen , toplanamaz nesneleri çizer
// daðlar 
void Texture :: draw_solid_texture(SDL_Renderer* texture_render) 
{
	SDL_Rect hedef_texture;

	for(int t=0;t<Collectible_Size;t++)
		{
			if(((Solid_Items[t].item_name) != "") && (Solid_Items[t].number_item > 0)) // nesne çizilecek
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
			
					if(Solid_Items[t].item_active == true) // nesnenin gerçek çizimi uygulanmýþsa
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

// Ýçinden geçilebilen , toplanamaz nesneleri çizer
// yer þekilleri , göl 
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
				if(SDL_HasIntersection(&hedef_texture , &meteor_rect))
				{
					if(Uncollectible_Items[i].item_name == "bullet_rifle")
					{
						meteor_health = meteor_health - 100;
					}
					else if(Uncollectible_Items[i].item_name == "bullet_handgun")
					{
						meteor_health = meteor_health - 100;
						active_bullet = false;
						z = 0;
						Uncollectible_Items[98].item_active = false;
					}
					else if(Uncollectible_Items[i].item_name == "bullet_shotgun")
					{
						meteor_health = meteor_health - 100;
					}
				}
				else
				{
					if(Uncollectible_Items[99].item_active || Uncollectible_Items[98].item_active || Uncollectible_Items[97].item_active)
						SDL_RenderCopyEx(texture_render , map_texture[Uncollectible_Items[i].item_name] , NULL , &hedef_texture , bullet_angle , 0 , SDL_FLIP_NONE);
				}
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

void Texture :: arkaplan_yükle(string dosya_yolu , SDL_Renderer* render_arkaplan)
{
	surface_background = IMG_Load(dosya_yolu.c_str());
	if(surface_background == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Texture" , "arkaplan yuklenemedi..!" , NULL);
		exit(0);
	}
	texture_background = SDL_CreateTextureFromSurface(render_arkaplan , surface_background);
	SDL_FreeSurface(surface_background);
}


void Texture :: draw_camera(SDL_Renderer* ren , int* pozx, int* pozy, int genislik , int yukseklik)
{
			
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
			
			
	SDL_RenderCopyEx(ren, texture_background , NULL , &camera , 0 , 0 , SDL_FLIP_NONE);
	
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
						Uncollectible_Items[99].item_rect.x = xpoz+50;
						Uncollectible_Items[99].item_rect.y = ypoz+50;
						Uncollectible_Items[99].item_rect.w = 30;
						Uncollectible_Items[99].item_rect.h = 10;
						Uncollectible_Items[99].item_active = true;
						Uncollectible_Items[99].item_name = "bullet_rifle";
						bullet_angle = angle;
					}
					draw_texture(rend);
					Uncollectible_Items[99].item_rect.x = (Uncollectible_Items[99].item_rect.x) + 1;
					z++;				
				}
				else if(barbaros_guns == "handgun")
				{
					if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							Uncollectible_Items[98].item_rect.x = xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							Uncollectible_Items[98].item_rect.y = ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							Uncollectible_Items[98].item_rect.x = xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							Uncollectible_Items[98].item_rect.y = ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							Uncollectible_Items[98].item_rect.x = xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							Uncollectible_Items[98].item_rect.y = ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							Uncollectible_Items[98].item_rect.x = xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							Uncollectible_Items[98].item_rect.y = ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						Uncollectible_Items[98].item_rect.w = 20;
						Uncollectible_Items[98].item_rect.h = 5;
						Uncollectible_Items[98].item_active = true;
						Uncollectible_Items[98].item_name = "bullet_handgun";
						
					}
					if(bullet_angle == 270)
					{
						Uncollectible_Items[98].item_rect.y = (Uncollectible_Items[98].item_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sað üst
					{
						Uncollectible_Items[98].item_rect.x = (Uncollectible_Items[98].item_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						Uncollectible_Items[98].item_rect.y = (Uncollectible_Items[98].item_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						Uncollectible_Items[98].item_rect.x = (Uncollectible_Items[98].item_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						Uncollectible_Items[98].item_rect.y = (Uncollectible_Items[98].item_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						Uncollectible_Items[98].item_rect.x = (Uncollectible_Items[98].item_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						Uncollectible_Items[98].item_rect.y = (Uncollectible_Items[98].item_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sað alt
					{
						Uncollectible_Items[98].item_rect.x = (Uncollectible_Items[98].item_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						Uncollectible_Items[98].item_rect.y = (Uncollectible_Items[98].item_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}
					
					draw_texture(rend);
					z++;	
					
				}
				else if(barbaros_guns == "shotgun")
				{
					if(z == 0)
					{
						Uncollectible_Items[97].item_rect.x = xpoz+50;
						Uncollectible_Items[97].item_rect.y = ypoz+50;
						Uncollectible_Items[97].item_rect.w = 30;
						Uncollectible_Items[97].item_rect.h = 10;
						Uncollectible_Items[97].item_active = true;
						Uncollectible_Items[97].item_name = "bullet_shotgun";
						bullet_angle = angle;
					}
					draw_texture(rend);
					Uncollectible_Items[97].item_rect.x = (Uncollectible_Items[97].item_rect.x) + 1;
					z++;	
				}
		}
		else if(z >= 50) // menzili aþtýysa çizmeyi býrak
		{
			z=0;
			active_bullet = false;

			Uncollectible_Items[97].item_active = false;
			Uncollectible_Items[98].item_active = false;
			Uncollectible_Items[99].item_active = false;	
		}
	}
	else // active_bullet = false ise mermi çizimi olmayacak
	{
		z=0;
		Uncollectible_Items[97].item_active = false;
		Uncollectible_Items[98].item_active = false;
		Uncollectible_Items[99].item_active = false;

	}
}

void Texture :: load_textures(SDL_Renderer* renderer)
{
	load("assets/guns/health_bag.png", "health_bag", renderer);
	load("assets/guns/full_bag.png", "full_bag", renderer);
	load("assets/guns/handgun_mermi.png", "handgun_mermi", renderer);
	load("assets/guns/shotgun_mermi.png", "shotgun_mermi", renderer);
	load("assets/guns/rifle.png", "rifle", renderer);
	load("assets/guns/shotgun.png", "shotgun", renderer);
	load("assets/guns/handgun.png", "handgun", renderer);		
	load("assets/guns/knife.png", "knife", renderer);
	load("assets/rock_1.png", "rock_1", renderer);
	load("assets/kuru_agac.png", "kuru_agac", renderer);
	load("assets/stone_wall.png", "stone_wall", renderer);
	load("assets/shoot.png", "shoot", renderer);
	load("assets/Sepia.png", "sepia", renderer);

	load("assets/guns/energy water.png", "energy_water", renderer);
	load("assets/crater1.png", "krater1", renderer);
	load("assets/guns/bullet_handgun.png", "bullet_handgun", renderer);
	load("assets/guns/bullet_shotgun.png", "bullet_shotgun", renderer);
	
	Envanter_Yukle("assets/18_envanter.png", "full_envanter", renderer);
	Envanter_Yukle("assets/12_envanter.png", "12_envanter", renderer);
	Envanter_Yukle("assets/9_envanter.png", "9_envanter", renderer);
}