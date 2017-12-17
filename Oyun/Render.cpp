#include <iostream>
#include <string>
#include "Render.h"
#include "SDL/SDL.h"
#include <stdlib.h> // srand i�in
#include <Time.h> // time i�in
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <GL/freeglut.h>

using namespace std;

Render :: Render()
{
	total = 0; // �l��len zaman� tutar (milisaniye)
	
	world_x = 0;
	world_y = 0;
	world_w = 3000;
	world_h = 1500;
	z=0;
	fpsTime = 0;
	
}

Render :: ~Render()
{

}

void Render :: render(SDL_Renderer* rend , bool menu)
{	
	start = SDL_GetTicks();
	
	srand ((unsigned int)time(NULL));
	//SDL_RenderSetViewport(rend , &viewport);
	// EKRANI TEM�ZLE
	SDL_RenderClear(rend); 
	
	// BACKGROUND
	draw_camera(rend, &xpoz , &ypoz , 1350, 700);

	drawAirplane(rend , camera.x , camera.y , start);

	if(creature_health > 0)
		drawCreature(rend , camera.x , camera.y , start);
	// ITEMS

		// toplanabilir nesneleri �izece�iz
		draw_object(rend , start ); 

		// toplanamaz ve i�inden ge�ilebilir nesneleri �izece�iz -> mermi , su , ta� , ot , di�er yer �ekilleri
		draw_texture(rend);

		// toplanamaz ve i�inden ge�ilemez nesneleri �izece�iz -> da� , a�a� kaya
		draw_solid_texture(rend);

		draw_bullet(rend);
		
	if(health > 0)
	{
		gece_g�nd�z(rend , start); // gece g�nd�z d�ng�s�
	}

	if(health > 0)
	{		
		barbaros_�iz(rend , barbaros_guns , &xpoz , &ypoz , camera.x , camera.y , barbaros_durum , start); // ana karakteri �iz
	}

	barbaros_g�ncelle(rend , start); // susuzluk durumu , sa�l�k durumu , mermi durumu , a�l�k durumunu g�ncelle

	//SDL_RenderSetScale(rend , 0.5 , 0.5);
	
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
	if(health > 0)
	{
		item_information(rend , inf);
		item_bilgi(rend , inf);
	}
	// Crafting Men�s�
	
	if(statu_crafting && health > 0)
		crafting(rend);
	
	player_information(rend);

	// ENVANTER 
	if(envanter_durum == "full_envanter")
		Envanter_�iz("full_envanter", 100 , 670 , 1150 , 50 , rend); // 18 birimlik envanter �izer

	if(envanter_durum == "12_envanter")
		Envanter_�iz("12_envanter", 292 , 670 , 765 , 50 , rend); // 12 birimlik envanter �izer

	if(envanter_durum == "9_envanter")
		Envanter_�iz("9_envanter", 387 , 670 , 575 , 50 , rend); // 9 birimlik envanter �izer
	
	Envanter_G�ncelle(rend); // envanterdeki t�m nesneleri �izer
	Envanter(rend);

	
	//SDL_RenderSetLogicalSize(rend , 300 , 300);
	informationItem(rend);
	//tank(rend , camera.x , camera.y);
	SDL_RenderCopyEx(rend, map_texture[current_cursor] , NULL , &solid_mouse , 0 , 0 , SDL_FLIP_NONE);
	// EKRANI G�NCELLE
	
	SDL_RenderPresent(rend); 

	// Toplam s�reyi hesapla
	deltaclock = SDL_GetTicks() - start;
	total = total + deltaclock;
	//current_time = current_time + deltaclock;
	fpsTime += deltaclock;

	// calculate FPS  
	//if(deltaclock > 0.0)
	currentFPS = 1000.0 / deltaclock;

	// write FPS
	if(fpsTime > 1000.0)
	{
		SDL_SetWindowTitle(win , (to_string(int(currentFPS))).c_str());
	}

	if(fpsTime >= 1000.0)
	{
		fpsTime = 0;
	}
	
}
