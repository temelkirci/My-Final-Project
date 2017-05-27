#include <iostream>
#include <string>
#include "Render.h"
#include "SDL/SDL.h"
#include <stdlib.h> // srand i�in
#include <Time.h> // time i�in

using namespace std;

Render :: Render()
{
	total = 0; // �l��len zaman� tutar (milisaniye)
	
	world_x = 0;
	world_y = 0;
	world_w = 3000;
	world_h = 1500;
	z=0;
}

Render :: ~Render()
{

}

void Render :: render(SDL_Renderer* rend , bool menu)
{	
	start = SDL_GetTicks();
	srand ((unsigned int)time(NULL));
	
	// EKRANI TEM�ZLE
	SDL_RenderClear(rend); 
	
	// BACKGROUND
	draw_camera(rend, &xpoz , &ypoz , 1350, 700);
	
	draw_bullet(rend); // mermi �izer

	// ITEMS

		// toplanabilir nesneleri �izece�iz
		draw_object(rend); 

		// toplanamaz ve i�inden ge�ilemez nesneleri �izece�iz -> da� , a�a� kaya
		draw_solid_texture(rend);

		// toplanamaz ve i�inden ge�ilebilir nesneleri �izece�iz -> mermi , su , ta� , ot , di�er yer �ekilleri
		draw_texture(rend);

	barbaros_�iz(rend , barbaros_guns , &xpoz , &ypoz , camera.x , camera.y , barbaros_durum , current_time); // ana karakteri �iz

	draw_enemy(rend , current_time , camera.x , camera.y);
	draw_trex(rend , current_time , &xpoz , &ypoz , angle , camera.x , camera.y);

	gece_g�nd�z(rend , current_time); // gece g�nd�z d�ng�s�
	
	barbaros_g�ncelle(rend , current_time); // susuzluk durumu , sa�l�k durumu , mermi durumu , a�l�k durumunu g�ncelle
	//Lamp(rend , camera.x , camera.y);
	// Karakter bilgilerini �iz ve g�ncelle
	if(barbaros_guns == "handgun")
	{
		barbaros_status(rend , 15 , 15 , 20 , 20 , health , handgun_mermi , hunger , thirtsy);
	}
	else if(barbaros_guns == "rifle")
	{
		barbaros_status(rend , 15 , 15 , 20 , 20 , health , rifle_mermi , hunger , thirtsy);
	}
	else if(barbaros_guns == "shotgun")
	{
		barbaros_status(rend , 15 , 15 , 20 , 20 , health , shotgun_mermi , hunger , thirtsy);
	}
	else
	{
		barbaros_status(rend , 15 , 15 , 20 , 20 , health , 0 , hunger , thirtsy); // knife i�in mermi say�s� 0
	}

	item_information(rend , inf);
	item_bilgi(rend , inf);

	// Crafting Men�s�
	
	if(statu_crafting)
		crafting(rend);
	
	player_information(rend);

	// ENVANTER 
	if(envanter_durum == "full_envanter")
		Envanter_�iz("full_envanter", 100 , 650 , 1150 , 50 , rend); // 18 birimlik envanter �izer

	if(envanter_durum == "12_envanter")
		Envanter_�iz("12_envanter", 292 , 650 , 765 , 50 , rend); // 12 birimlik envanter �izer

	if(envanter_durum == "9_envanter")
		Envanter_�iz("9_envanter", 387 , 650 , 575 , 50 , rend); // 9 birimlik envanter �izer
	
	Envanter_G�ncelle(rend); // envanterdeki t�m nesneleri �izer
	
	/*
	// calculate FPS  
	if(deltaclock > 0)
		currentFPS = 1000 / deltaclock;
	// write FPS
	if((current_time / 1000)%2 == 0)
		cout<<endl<<currentFPS<<endl;
	
	*/

	// Toplam s�reyi hesapla
	deltaclock = SDL_GetTicks() - start;
	total = total + deltaclock;
	current_time = current_time + deltaclock;
	
	SDL_RenderCopyEx(rend, map_texture[current_cursor] , NULL , &solid_mouse , 0 , 0 , SDL_FLIP_NONE);
	// EKRANI G�NCELLE
	SDL_RenderPresent(rend); 
}
