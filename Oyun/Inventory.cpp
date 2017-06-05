#include <iostream>
#include <tuple>
#include <SDL/SDL.h>
#include "Inventory.h"
#include "Texture.h"
#include <SDL/SDL_image.h>
#include <string>
#include <map>

using namespace std;

Inventory :: Inventory()
{
	inventory_size = 0; // envanterde sadece b��ak olacak
	
	for(int i=0;i<18;i++)
	{
		get<0>(envanter[i]) = "";
		get<2>(envanter[i]) = 0; // e�ya say�s� 0 olsun
	}
	
	envanter_durum = "9_envanter" ;
	max_envanter = 9;

	inventory_color.r = 0;
	inventory_color.g = 0;
	inventory_color.b = 0;

	rect_inventory.y=670;
}

Inventory :: ~Inventory()
{

}

void Inventory :: Envanter_Yukle(string envanter_dosya, string envanter_adi, SDL_Renderer* render)
{
	SDL_Surface * envanter_surface = IMG_Load(envanter_dosya.c_str());
	if(envanter_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Envanter" , "Envanter yuklenemedi..!" , NULL);
		exit(0);
	}
	envanter_texture = SDL_CreateTextureFromSurface(render , envanter_surface);
	SDL_FreeSurface(envanter_surface);
	if(envanter_texture != 0)
	{
		envanter_draw[envanter_adi] = envanter_texture; // T�m textureleri saklayaca��m�z yer
	}
}

void Inventory :: Envanter_�iz(string esya_adi, int envanter_x , int envanter_y , int envanter_genislik , int envanter_yukseklik , SDL_Renderer* rend)
{
	SDL_Rect hedef;
			hedef.x=envanter_x;
			hedef.y=envanter_y;
			hedef.w=envanter_genislik;
			hedef.h=envanter_yukseklik;

	rect_inventory.x=envanter_x;
	rect_inventory.y=envanter_y;
	rect_inventory.w = envanter_genislik;
	rect_inventory.h = envanter_yukseklik;

	SDL_RenderCopyEx(rend, envanter_draw[esya_adi] , NULL , &hedef , 0 , 0 , SDL_FLIP_NONE);
}


void Inventory :: Esya_Ekle(string esya_adi , int eklenecek_aded , SDL_Renderer* esya_render , SDL_Texture* esya_texture)
{
	if(inventory_size < max_envanter)
	{
		for(int i=0;i<18;i++)
		{
			if((get<0>(envanter[i]) == "") && (get<2>(envanter[i]) <= 0)) // e�ya envanterde yoksa
			{
				get<0>(envanter[i]) = esya_adi;
				get<1>(envanter[i]) = esya_texture;
				get<2>(envanter[i]) = eklenecek_aded;
				inventory_size++;
				break;
			}
			else if(get<0>(envanter[i]) == esya_adi) // e�ya envanterde varsa
			{
				if(get<2>(envanter[i]) < 9) // her e�yadan maximum 9 tane olabilir
				{
					get<2>(envanter[i]) = get<2>(envanter[i]) + 1;			
					break;
				}
				else
				{
					get<2>(envanter[i]) = 9;
					cout<<esya_adi<<" sayisi 9 u gecemez"<<endl;
				}
			}
				
		}	
	}
	else
	{
		cout<<"Envanter Dolu"<<endl;
	}
	
}

void Inventory :: Envanter_G�ncelle(SDL_Renderer* rend)
{
	SDL_Rect esya;
	SDL_Rect yazi;

	int x;
	int a=0;
	
	if(max_envanter == 18)
	{
		x=110;
		rect_inventory.x=x;
	}
	else if(max_envanter == 12)
	{
		x=302;
		rect_inventory.x=x;
		
	}
	else if(max_envanter == 9)
	{
		x=397;
		rect_inventory.x=x;
		
	}
	// esyanin yuksekli�i 30
	// esyanin genisli�i 40
	
	for(int t=0;t<max_envanter;t++)
	{
		
		esya.x = x+a;
		esya.y = 685;
		esya.w = 40;
		esya.h = 30;
							
		if(get<2>(envanter[t]) > 0) // e�ya say�s� 1 den fazlaysa
		{
			get<3>(envanter[t]) = esya.x; // esya x-koordinat�
			get<4>(envanter[t]) = esya.y; // esya y-koordinat�

			SDL_SetTextureBlendMode(get<1>(envanter[t]) , SDL_BLENDMODE_BLEND);
			SDL_RenderCopyEx(rend, get<1>(envanter[t]) , NULL , &esya , 0 , 0 , SDL_FLIP_NONE);	// e�yay� �iz
					
			yazi.x = esya.x-7;
			yazi.y = esya.y-13;
			yazi.w = 10;
			yazi.h = 12;

			string adet_deger = to_string(get<2>(envanter[t]));
			char* adet_yaz = _strdup(adet_deger.c_str());

			SDL_Surface* textSurface = TTF_RenderText_Blended(Font , adet_yaz , inventory_color );
			adet_texture = SDL_CreateTextureFromSurface( rend, textSurface );
			SDL_FreeSurface(textSurface);

			SDL_RenderCopyEx(rend , adet_texture , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(adet_texture);
			
			a=a+65;			
		}
		
		else if(get<2>(envanter[t]) <= 0) // e�ya yoksa
		{
			get<0>(envanter[t]) = ""; // e�ya ismini s�f�rla
			get<1>(envanter[t]) = NULL; // e�ya textureyi s�f�rla
			get<2>(envanter[t]) = 0; // e�ya say�s�n� 0 yap
			get<3>(envanter[t]) = NULL; // esya x-koordinat�
			get<4>(envanter[t]) = NULL; // esya y-koordinat�
		}	
	}							
}