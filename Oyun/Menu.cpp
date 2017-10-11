#include <iostream>
#include "Menu.h"
#include <SDL/SDL_image.h>
#include <string>
#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

using namespace std;

Menu :: Menu()
{
	back = Mix_LoadMUS("assets/sounds/menu.ogg");
	
	SDL_ShowCursor(SDL_DISABLE);

	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;
	text_color.a = 100;

	start_button.x = 550;
	start_button.y = 200;
	start_button.w = 200;
	start_button.h = 50;

	save_button.x = 550;
	save_button.y = 280;
	save_button.w = 200;
	save_button.h = 50;

	load_button.x = 550;
	load_button.y = 360;
	load_button.w = 200;
	load_button.h = 50;

	credits_button.x = 550;
	credits_button.y = 440;
	credits_button.w = 200;
	credits_button.h = 50;

	exit_button.x = 550;
	exit_button.y = 520;
	exit_button.w = 200;
	exit_button.h = 50;

	men�_mouse.x = 675;
	men�_mouse.y = 345;

	button_array[0] = "START";
	button_array[1] = "SAVE";
	button_array[2] = "LOAD";
	button_array[3] = "CREDITS";
	button_array[4] = "EXIT";

	menu_surface = NULL ;
	menu_texture = NULL ;
}

Menu :: ~Menu()
{
	SDL_DestroyTexture(menu_texture);
	SDL_FreeSurface(menu_surface);
	
	menu_surface = NULL ;
	menu_texture = NULL ;
}

void Menu :: menu_yukle(char* men�_yolu,SDL_Renderer* menu_render )
{
	menu_font = TTF_OpenFont("fonts/fontss.ttf", 100);

	menu_surface = IMG_Load(men�_yolu);
	if(menu_surface == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Menu" , "Men� yuklenemedi..!" , NULL);
		exit(0);
	}
	menu_texture = SDL_CreateTextureFromSurface(menu_render , menu_surface);
	SDL_FreeSurface(menu_surface);
}

bool Menu :: loadPathMenu(char* dosya_adi , string texture_adi , SDL_Renderer* texture_render)
{
	surface_buttons = IMG_Load(dosya_adi);
	
	if(surface_buttons == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Menu" , "Menu :: load_buttons (surface_buttons yuklenemedi..!)" , NULL);
		cout<<texture_adi<<endl;
		//exit(0);
	}

	texture_buttons = SDL_CreateTextureFromSurface(texture_render , surface_buttons);	// y�zeyi renderleyerek texture olu�tur	
	SDL_FreeSurface(surface_buttons);
	if(texture_buttons != 0)
	{
		map_button[texture_adi] = texture_buttons; // T�m textureleri saklayaca��m�z yer
		
		return true;
	}
	return false;
}

void Menu :: menu_goster(SDL_Renderer* render_menu , int x , int y , int genislik , int yukseklik )
{
	SDL_ShowCursor(SDL_DISABLE);
	SDL_RenderClear(render_menu); // renderi temizle

	SDL_Rect menu_background;
	menu_background.x=x;
	menu_background.y=y;
	menu_background.w=genislik;
	menu_background.h=yukseklik;

	SDL_RenderCopyEx(render_menu , menu_texture , NULL , &menu_background , 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderCopyEx(render_menu , map_button["START"] , NULL , &start_button , 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(render_menu , map_button["SAVE"] , NULL , &save_button , 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(render_menu , map_button["LOAD"] , NULL , &load_button , 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(render_menu , map_button["CREDITS"] , NULL , &credits_button , 0 , 0 , SDL_FLIP_NONE);
	SDL_RenderCopyEx(render_menu , map_button["EXIT"] , NULL , &exit_button , 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderCopyEx(render_menu, map_button["sepia"] , NULL , &men�_mouse , 0 , 0 , SDL_FLIP_NONE);

	SDL_RenderPresent(render_menu);
}

bool Menu :: klavye_mouse(bool baslat)
{
	ev;
	int x , y;	

	SDL_GetMouseState(&x,&y);

	men�_mouse.x=x;
	men�_mouse.y=y;
	men�_mouse.w=30;
	men�_mouse.h=30;

	while(SDL_PollEvent(&ev) != 0)
	{
		switch(ev.type)
		{
			case SDL_QUIT :// sa� �stteki �arp�ya basarsa oyunu kapat
				
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				// Play tu�una bas�l�rsa
				if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&men�_mouse , &start_button)))
				{
					Mix_HaltMusic(); // Arkaplan m�zi�ini durdur
					Mix_PlayMusic(back,-1); // oyun m�zi�ini ba�lat
					baslat = true;
					SDL_ShowCursor(SDL_DISABLE);
					return baslat; // Oyunu ba�lat
					break;					
					
				}
				// Credits tu�una bas�l�rsa
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&men�_mouse , &save_button)))
				{					
					cout<<"Oyun Kaydedildi"<<endl;
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&men�_mouse , &load_button)))
				{
					cout<<"Oyun Y�kleniyor"<<endl;
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&men�_mouse , &credits_button)))
				{
					cout<<"Oyun Hakkinda"<<endl;
					break;
				}
				else if((ev.button.button == SDL_BUTTON_LEFT) && (SDL_HasIntersection(&men�_mouse , &exit_button)))
				{
					exit(0);
					SDL_Quit();
					break;
				}
				break;
		}
	}
		
	return baslat;
}

void Menu :: loadMenu(SDL_Renderer* renderer)
{
	menu_yukle("assets/menu.jpg", renderer);
	loadPathMenu("assets/buttons/START.png", "START",renderer);
	loadPathMenu("assets/buttons/SAVE.png", "SAVE",renderer);
	loadPathMenu("assets/buttons/LOAD.png", "LOAD",renderer);
	loadPathMenu("assets/buttons/CREDITS.png", "CREDITS",renderer);
	loadPathMenu("assets/buttons/EXIT.png", "EXIT",renderer);
	loadPathMenu("assets/Sepia.png", "sepia", renderer);
	
}