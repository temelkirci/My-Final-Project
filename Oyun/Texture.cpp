﻿#include "Texture.h"

#define PI 3.14159265 // Radyan dan dereceye çevirmek için kullanacağız

Texture :: Texture()
{
	/*
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
	*/
}

Texture :: ~Texture()
{
	/*
	SDL_FreeSurface(load_surface);
	SDL_DestroyTexture(load_texture);
	SDL_FreeSurface(surface_background);
	SDL_DestroyTexture(texture_background);
	
	load_surface = NULL;
	load_texture = NULL ;
	surface_background = NULL ;
	texture_background = NULL ;
	*/
}

/*
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
		mTextureMap[texture_adi] = load_texture; // Tüm textureleri saklayacağımız yer
		return true;
	}
	return false;
}

void Texture :: draw_camera(SDL_Renderer* ren , double pozx, double pozy, int genislik , int yukseklik)
{
	
}

void Texture :: item_bilgi(SDL_Renderer* ren , string inf_text)
{
	Write(ren , 0 , inf_text , 3000);
}

void Texture :: draw_object(SDL_Renderer* texture_render , Uint32 collectible_time) 
{
	SDL_Rect temp;

	SDL_Rect barbaros_rect = {(int)xpoz , (int)ypoz , 100 , 100};

	for(vector<Item>::iterator i = col.begin() ; i != col.end(); ++i)
	{
		temp = (*i).item_rect;

		if((*i).item_active) // obje çizilecekse
		{
			SDL_Rect hedef_texture = {(*i).item_rect.x + camera.x , (*i).item_rect.y + camera.y , (*i).item_rect.w , (*i).item_rect.h};		
			
		
				SDL_RenderCopyEx(texture_render , map_texture[(*i).item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
			
				if(SDL_HasIntersection(&temp , &barbaros_rect) && (inventory_size < max_envanter)) // barbaros eşyaya temas ettiyse
				{
					Esya_Ekle((*i).item_name , 1 , texture_render , map_texture[(*i).item_name]);

					if(((*i).item_name == "handgun") || ((*i).item_name == "shotgun") || ((*i).item_name == "rifle") || ((*i).item_name == "knife"))
					{
						(*i).item_name = "";
						(*i).item_blendmode = "";
						(*i).number_item = NULL;
						(*i).item_health = NULL;
						(*i).item_rect.x = NULL;
						(*i).item_rect.y = NULL;
						(*i).item_rect.w = NULL;
						(*i).item_rect.h = NULL;
						(*i).item_texture = NULL;
					}
					else // yeni eşya koordinatları üret
					{
						while(!randomPosition((*i).item_rect.w , (*i).item_rect.h , (*i)))
						{
							cout<<"Detected Collision"<<endl;
						}
					}
				}
				else if((inventory_size >= max_envanter) && (SDL_HasIntersection(&temp , &barbaros_rect)))
				{
					Write(texture_render , collectible_time , "Envanter Full" , -1);
				}
		}
	} // en dıştaki for
}
	
// İçinden geçilemeyen , toplanamaz nesneleri çizer
// dağlar 

void Texture :: draw_solid_texture(SDL_Renderer* texture_render) 
{
	
	for(vector<Item>::iterator t = solid.begin() ; t != solid.end(); ++t)
		{
			if((((*t).item_name) != "") && ((*t).item_health > 0)) // nesne çizilecek
			{
				SDL_Rect hedef_texture = {(*t).item_rect.x + camera.x , (*t).item_rect.y + camera.y , (*t).item_rect.w , (*t).item_rect.h};
				
				if((*t).item_blendmode == "add")
					SDL_SetTextureBlendMode(map_texture[(*t).item_name] , SDL_BLENDMODE_ADD);
				else if((*t).item_blendmode == "blend")
					SDL_SetTextureBlendMode(map_texture[(*t).item_name] , SDL_BLENDMODE_BLEND);
					
				SDL_RenderCopyEx(texture_render , map_texture[(*t).item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
				
				SDL_Rect barbaros_rect = {(int)xpoz , (int)ypoz , 100 , 100};

				SDL_Rect temp = (*t).item_rect;
			
				if(((*t).item_active) == true)
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
	
	for(vector<Item>::iterator i = uncol.begin() ; i != uncol.end(); ++i)
	{
		if((*i).item_name != "" && (*i).item_active == true)
		{
			SDL_Rect hedef_texture = {(*i).item_rect.x + camera.x , (*i).item_rect.y + camera.y , (*i).item_rect.w , (*i).item_rect.h};
	
			SDL_Rect barbaros_rect = {(int)xpoz , (int)ypoz , 100 , 100};

				// SDL_BLENDMODE_NONE : nesneyi görünmez yapar ve çizer
				// SDL_BLENDMODE_BLEND : nesneyi normal çizer
				// SDL_BLENDMODE_ADD : nesneyi parlak çizer

				SDL_RenderCopyEx(texture_render , map_texture[(*i).item_name] , NULL , &hedef_texture , 0 , 0 , SDL_FLIP_NONE);
			
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


void Texture :: draw_bullet(SDL_Renderer* rend , double camx , double camy)
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
							bullet_rifle.bullet_rect.x = (int)xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							bullet_rifle.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							bullet_rifle.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							bullet_rifle.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							bullet_rifle.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							bullet_rifle.bullet_rect.y = (int)ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							bullet_rifle.bullet_rect.x = (int)xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							bullet_rifle.bullet_rect.y = (int)ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						bullet_rifle.bullet_rect.w = 20;
						bullet_rifle.bullet_rect.h = 5;
						bullet_rifle.bullet_active = true;
						bullet_rifle.bullet_name = "bullet_rifle";
						
					}

					if(bullet_angle == 270)
					{
						bullet_rifle.bullet_rect.y = (bullet_rifle.bullet_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						bullet_rifle.bullet_rect.x = (bullet_rifle.bullet_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						bullet_rifle.bullet_rect.y = (bullet_rifle.bullet_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						bullet_rifle.bullet_rect.x = (bullet_rifle.bullet_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						bullet_rifle.bullet_rect.y = (bullet_rifle.bullet_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						bullet_rifle.bullet_rect.x = (bullet_rifle.bullet_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						bullet_rifle.bullet_rect.y = (bullet_rifle.bullet_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						bullet_rifle.bullet_rect.x = (bullet_rifle.bullet_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						bullet_rifle.bullet_rect.y = (bullet_rifle.bullet_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}

					SDL_Rect bul;
					bul.x = bullet_rifle.bullet_rect.x + (int)camx;
					bul.y = bullet_rifle.bullet_rect.y + (int)camy;
					bul.w = bullet_rifle.bullet_rect.w;
					bul.h = bullet_rifle.bullet_rect.h;

					if(bullet_rifle.bullet_active)
						SDL_RenderCopyEx(rend , map_texture[bullet_rifle.bullet_name] , NULL , &bul , bullet_angle , 0 , SDL_FLIP_NONE);
					z++;		
			
				}
				else if(barbaros_guns == "handgun")
				{

					if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							bullet_handgun.bullet_rect.x = (int)xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							bullet_handgun.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							bullet_handgun.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							bullet_handgun.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							bullet_handgun.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							bullet_handgun.bullet_rect.y = (int)ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							bullet_handgun.bullet_rect.x = (int)xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							bullet_handgun.bullet_rect.y = (int)ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						bullet_handgun.bullet_rect.w = 20;
						bullet_handgun.bullet_rect.h = 5;
						bullet_handgun.bullet_active = true;
						bullet_handgun.bullet_name = "bullet_handgun";
						
					}
					if(bullet_angle == 270)
					{
						bullet_handgun.bullet_rect.y = (bullet_handgun.bullet_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						bullet_handgun.bullet_rect.x = (bullet_handgun.bullet_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						bullet_handgun.bullet_rect.y = (bullet_handgun.bullet_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						bullet_handgun.bullet_rect.x = (bullet_handgun.bullet_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						bullet_handgun.bullet_rect.y = (bullet_handgun.bullet_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						bullet_handgun.bullet_rect.x = (bullet_handgun.bullet_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						bullet_handgun.bullet_rect.y = (bullet_handgun.bullet_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						bullet_handgun.bullet_rect.x = (bullet_handgun.bullet_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						bullet_handgun.bullet_rect.y = (bullet_handgun.bullet_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}

					SDL_Rect bul;
					bul.x = bullet_handgun.bullet_rect.x + (int)camx;
					bul.y = bullet_handgun.bullet_rect.y + (int)camy;
					bul.w = bullet_handgun.bullet_rect.w;
					bul.h = bullet_handgun.bullet_rect.h;

					if(bullet_handgun.bullet_active)
						SDL_RenderCopyEx(rend , map_texture[bullet_handgun.bullet_name] , NULL , &bul , bullet_angle , 0 , SDL_FLIP_NONE);
					z++;	
					
				}
				else if(barbaros_guns == "shotgun")
				{

					if(z == 0)
					{	
						bullet_angle = angle;

						if(bullet_angle >= 0 && bullet_angle <90)
						{
							bullet_shotgun.bullet_rect.x = (int)xpoz + 90 - (int)(30*cos((bullet_angle*PI)/180));
							bullet_shotgun.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 90 && bullet_angle <180)
						{
							bullet_shotgun.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((90-bullet_angle*PI)/180));
							bullet_shotgun.bullet_rect.y = (int)ypoz + 70 - (int)(30*sin((90-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 180 && bullet_angle <270)
						{
							bullet_shotgun.bullet_rect.x = (int)xpoz + 20 + (int)(30*cos((180-bullet_angle*PI)/180));
							bullet_shotgun.bullet_rect.y = (int)ypoz + 25 + (int)(30*sin((180-bullet_angle*PI)/180));
						}
						else if(bullet_angle >= 270 && bullet_angle <360)
						{
							bullet_shotgun.bullet_rect.x = (int)xpoz + 70 - (int)(30*cos((270-bullet_angle*PI)/180));
							bullet_shotgun.bullet_rect.y = (int)ypoz + 20 + (int)(30*sin((270-bullet_angle*PI)/180));
						}
						
						bullet_shotgun.bullet_rect.w = 20;
						bullet_shotgun.bullet_rect.h = 5;
						bullet_shotgun.bullet_active = true;
						bullet_shotgun.bullet_name = "bullet_shotgun";
						
					}
					if(bullet_angle == 270)
					{
						bullet_shotgun.bullet_rect.y = (bullet_shotgun.bullet_rect.y) - 1;
					}
					
					if(bullet_angle >= 270) // sağ üst
					{
						bullet_shotgun.bullet_rect.x = (bullet_shotgun.bullet_rect.x) + (int)(10*cos(((360-bullet_angle)*PI)/180));
						bullet_shotgun.bullet_rect.y = (bullet_shotgun.bullet_rect.y) - (int)(10*sin(((360-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 180 && bullet_angle < 270) // sol üst
					{
						bullet_shotgun.bullet_rect.x = (bullet_shotgun.bullet_rect.x) - (int)(10*cos(((bullet_angle-180)*PI)/180));
						bullet_shotgun.bullet_rect.y = (bullet_shotgun.bullet_rect.y) - (int)(10*sin(((bullet_angle-180)*PI)/180));

					}
					else if(bullet_angle >= 90 && bullet_angle < 180) // sol alt
					{
						bullet_shotgun.bullet_rect.x = (bullet_shotgun.bullet_rect.x) - (int)(10*cos(((180-bullet_angle)*PI)/180));
						bullet_shotgun.bullet_rect.y = (bullet_shotgun.bullet_rect.y) + (int)(10*sin(((180-bullet_angle)*PI)/180));
					}
					else if(bullet_angle >= 0 && bullet_angle < 90) // sağ alt
					{
						bullet_shotgun.bullet_rect.x = (bullet_shotgun.bullet_rect.x) + (int)(10*cos(((bullet_angle)*PI)/180));
						bullet_shotgun.bullet_rect.y = (bullet_shotgun.bullet_rect.y) + (int)(10*sin(((bullet_angle)*PI)/180));
					}

					SDL_Rect bul;
					bul.x = bullet_shotgun.bullet_rect.x + (int)camx;
					bul.y = bullet_shotgun.bullet_rect.y + (int)camy;
					bul.w = bullet_shotgun.bullet_rect.w;
					bul.h = bullet_shotgun.bullet_rect.h;

					if(bullet_shotgun.bullet_active)
						SDL_RenderCopyEx(rend , map_texture[bullet_shotgun.bullet_name] , NULL , &bul , bullet_angle , 0 , SDL_FLIP_NONE);
					z++;	
				}
					
		}

		if(z >= 50) // menzili aştıysa çizmeyi bırak
		{
			z=0;
			active_bullet = false;
			barbaros_durum = "move";
			bullet_shotgun.bullet_active = false;
			bullet_rifle.bullet_active = false;
			bullet_handgun.bullet_active = false;	
		}
	}
}


bool Texture :: randomPosition(int w , int h , Item &p)
{
	SDL_Rect temp = {rand()%6000 , rand()%1500 , w , h};

	for(vector<SDL_Rect>::iterator i = rect.begin() ; i != rect.end(); ++i)
	{
		if(  SDL_HasIntersection((&temp) , &(*i))  )
		{
			return false;
		}
	}

	p.item_rect = temp;

	cout<<"No Collision"<<p.item_rect.x<<"  "<<p.item_rect.y<<endl;
	return true;
}

void Texture :: loadTextures(SDL_Renderer* renderer)
{	
	// toplanabilir nesneler
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

	// Arkaplan nesnelerini yükle
	load("assets/guns/soup.png", "soup", renderer);
	load("assets/huge_box.jpg", "huge_box", renderer);
	load("assets/guns/rifle.png", "rifle", renderer);
	load("assets/crater.png", "crater", renderer);

	
	load("assets/guns/bullet_handgun.png", "bullet_handgun", renderer);
	load("assets/guns/bullet_shotgun.png", "bullet_shotgun", renderer);
	load("assets/guns/bullet_rifle.png", "bullet_rifle", renderer);
}
*/