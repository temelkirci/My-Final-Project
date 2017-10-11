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
	inventory_size = 0; // envanterde sadece býçak olacak
	
	for(int i=0;i<18;i++)
	{
		InventoryObject[i].objectName = "";
		InventoryObject[i].objectNumber = 0; // eþya sayýsý 0 olsun
	}

		envanter_color.r = 255;
		envanter_color.g = 0;
		envanter_color.b = 0;
		envanter_color.a = 0;

	infItem = "";
	InventoryStore.OpenInventory = false;

	InventoryStore.InventoryRect.x = 1050;
	InventoryStore.InventoryRect.y = 100;
	InventoryStore.InventoryRect.w = 300;
	InventoryStore.InventoryRect.h = 400;

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

void Inventory :: Envanter_Yukle(char* envanter_dosya, string envanter_adi, SDL_Renderer* render)
{
	SDL_Surface * envanter_surface = IMG_Load(envanter_dosya);
	if(envanter_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Envanter" , "Envanter yuklenemedi..!" , NULL);
		exit(0);
	}
	envanter_texture = SDL_CreateTextureFromSurface(render , envanter_surface);
	SDL_FreeSurface(envanter_surface);
	if(envanter_texture != 0)
	{
		envanter_draw[envanter_adi] = envanter_texture; // Tüm textureleri saklayacaðýmýz yer
	}
}

void Inventory :: Envanter_Çiz(string esya_adi, int envanter_x , int envanter_y , int envanter_genislik , int envanter_yukseklik , SDL_Renderer* rend)
{
	rect_inventory.x=envanter_x;
	rect_inventory.y=envanter_y;
	rect_inventory.w = envanter_genislik;
	rect_inventory.h = envanter_yukseklik;

	SDL_RenderCopyEx(rend, envanter_draw[esya_adi] , NULL , &rect_inventory , 0 , 0 , SDL_FLIP_NONE);
}


void Inventory :: Esya_Ekle(string esya_adi , int eklenecek_aded , SDL_Renderer* esya_render , SDL_Texture* esya_texture)
{
	if(inventory_size < max_envanter)
	{
		for(int i=0;i<18;i++)
		{
			if((InventoryObject[i].objectName == "") && (InventoryObject[i].objectNumber <= 0)) // eþya envanterde yoksa
			{
				InventoryObject[i].objectName = esya_adi;
				InventoryObject[i].objectTexture = esya_texture;
				InventoryObject[i].objectNumber = eklenecek_aded;
				inventory_size++;
				break;
			}
			else if(InventoryObject[i].objectName == esya_adi) // eþya envanterde varsa
			{
				if(InventoryObject[i].objectNumber < 9) // her eþyadan maximum 9 tane olabilir
				{
					InventoryObject[i].objectNumber = InventoryObject[i].objectNumber + 1;			
					break;
				}
				else
				{
					InventoryObject[i].objectNumber = 9;
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

void Inventory :: Envanter_Güncelle(SDL_Renderer* rend)
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
	// esyanin yuksekliði 30
	// esyanin genisliði 40
	
	for(int t=0;t<max_envanter;t++)
	{
		
		esya.x = x+a;
		esya.y = 685;
		esya.w = 40;
		esya.h = 30;
							
		if(InventoryObject[t].objectNumber > 0) // eþya sayýsý 1 den fazlaysa
		{
			InventoryObject[t].xCoord = esya.x; // esya x-koordinatý
			InventoryObject[t].yCoord = esya.y; // esya y-koordinatý

			SDL_SetTextureBlendMode(InventoryObject[t].objectTexture , SDL_BLENDMODE_BLEND);
			SDL_RenderCopyEx(rend, InventoryObject[t].objectTexture , NULL , &esya , 0 , 0 , SDL_FLIP_NONE);	// eþyayý çiz
					
			yazi.x = esya.x-7;
			yazi.y = esya.y-13;
			yazi.w = 10;
			yazi.h = 12;

			string adet_deger = to_string(InventoryObject[t].objectNumber);
			char* adet_yaz = _strdup(adet_deger.c_str());

			SDL_Surface* textSurface = TTF_RenderText_Blended(Font , adet_yaz , inventory_color );
			adet_texture = SDL_CreateTextureFromSurface( rend, textSurface );
			SDL_FreeSurface(textSurface);

			SDL_RenderCopyEx(rend , adet_texture , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
			SDL_DestroyTexture(adet_texture);
			
			a=a+65;			
		}
		
		else if(InventoryObject[t].objectNumber <= 0) // eþya yoksa
		{
			InventoryObject[t].objectName = ""; // eþya ismini sýfýrla
			InventoryObject[t].objectTexture = NULL; // eþya textureyi sýfýrla
			InventoryObject[t].objectNumber = 0; // eþya sayýsýný 0 yap
			InventoryObject[t].xCoord = NULL; // esya x-koordinatý
			InventoryObject[t].yCoord = NULL; // esya y-koordinatý
		}	
	}							
}

void Inventory :: deleteItem(string object_name , int delete_number)
{
	for(int t=0;t<inventory_size;t++)
	{
		if(InventoryObject[t].objectName == object_name)
		{
			InventoryObject[t].objectNumber = InventoryObject[t].objectNumber - delete_number;

			if(InventoryObject[t].objectNumber <= 0)
				inventory_size--;

			break;
		}
	}
	
}

void Inventory :: Envanter(SDL_Renderer* rend)
{
	if(InventoryStore.OpenInventory)
		SDL_RenderCopyEx(rend , envanter_draw["Inventory"] , NULL , &InventoryStore.InventoryRect , 0 , 0 , SDL_FLIP_NONE);
}

void Inventory :: informationItem(SDL_Renderer* rend)
{
	if(infItem != "")
	{
		for(int t=0;t<inventory_size;t++)
		{
			if(InventoryObject[t].objectName == infItem) // kutucuklarýn üzerindeyse
			{

				box.x = InventoryObject[t].xCoord - 15;
				box.y = InventoryObject[t].yCoord - 120;
				box.w = 80;
				box.h = 100;

				SDL_SetRenderDrawColor(rend , 255 , 255 , 255 , 100); 
				SDL_RenderFillRect(rend, &box);

				SDL_Rect yazi;
				yazi.x = InventoryObject[t].xCoord - 10;
				yazi.y = InventoryObject[t].yCoord - 110;
				yazi.w = 35;
				yazi.h = 15;
				
				SDL_Surface* temel = TTF_RenderText_Blended( Font , infItem.c_str() , envanter_color );
				SDL_Texture* yazii_texture = SDL_CreateTextureFromSurface(rend, temel );
				SDL_FreeSurface(temel);

				SDL_RenderCopyEx(rend , yazii_texture , NULL , &yazi , 0 , 0 , SDL_FLIP_NONE);
				SDL_DestroyTexture(yazii_texture);
			}
		}
	}
}

void Inventory :: loadInventory(SDL_Renderer* renderer)
{
	Envanter_Yukle("assets/18_envanter.png", "full_envanter", renderer);
	Envanter_Yukle("assets/12_envanter.png", "12_envanter", renderer);
	Envanter_Yukle("assets/9_envanter.png", "9_envanter", renderer);

	Envanter_Yukle("assets/envanter1.jpg", "Inventory", renderer);
}