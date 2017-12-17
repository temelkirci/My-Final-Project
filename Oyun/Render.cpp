#include <iostream>
#include <string>
#include "Render.h"
#include "SDL/SDL.h"
#include <stdlib.h> // srand için
#include <Time.h> // time için
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <GL/freeglut.h>

using namespace std;

Render :: Render()
{
	total = 0; // ölçülen zamaný tutar (milisaniye)
	
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
	// EKRANI TEMÝZLE
	SDL_RenderClear(rend); 
	
	// BACKGROUND
	draw_camera(rend, &xpoz , &ypoz , 1350, 700);

	drawAirplane(rend , camera.x , camera.y , start);

	if(creature_health > 0)
		drawCreature(rend , camera.x , camera.y , start);
	// ITEMS

		// toplanabilir nesneleri çizeceðiz
		draw_object(rend , start ); 

		// toplanamaz ve içinden geçilebilir nesneleri çizeceðiz -> mermi , su , taþ , ot , diðer yer þekilleri
		draw_texture(rend);

		// toplanamaz ve içinden geçilemez nesneleri çizeceðiz -> dað , aðaç kaya
		draw_solid_texture(rend);

		draw_bullet(rend);
		
	if(health > 0)
	{
		gece_gündüz(rend , start); // gece gündüz döngüsü
	}

	if(health > 0)
	{		
		barbaros_çiz(rend , barbaros_guns , &xpoz , &ypoz , camera.x , camera.y , barbaros_durum , start); // ana karakteri çiz
	}

	barbaros_güncelle(rend , start); // susuzluk durumu , saðlýk durumu , mermi durumu , açlýk durumunu güncelle

	//SDL_RenderSetScale(rend , 0.5 , 0.5);
	
	// Karakter bilgilerini çiz ve güncelle
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
		barbaros_status(rend , 15 , 15 , 20 , 20 , health , 0 , hunger , thirtsy); // knife için mermi sayýsý 0
	}
	if(health > 0)
	{
		item_information(rend , inf);
		item_bilgi(rend , inf);
	}
	// Crafting Menüsü
	
	if(statu_crafting && health > 0)
		crafting(rend);
	
	player_information(rend);

	// ENVANTER 
	if(envanter_durum == "full_envanter")
		Envanter_Çiz("full_envanter", 100 , 670 , 1150 , 50 , rend); // 18 birimlik envanter çizer

	if(envanter_durum == "12_envanter")
		Envanter_Çiz("12_envanter", 292 , 670 , 765 , 50 , rend); // 12 birimlik envanter çizer

	if(envanter_durum == "9_envanter")
		Envanter_Çiz("9_envanter", 387 , 670 , 575 , 50 , rend); // 9 birimlik envanter çizer
	
	Envanter_Güncelle(rend); // envanterdeki tüm nesneleri çizer
	Envanter(rend);

	
	//SDL_RenderSetLogicalSize(rend , 300 , 300);
	informationItem(rend);
	//tank(rend , camera.x , camera.y);
	SDL_RenderCopyEx(rend, map_texture[current_cursor] , NULL , &solid_mouse , 0 , 0 , SDL_FLIP_NONE);
	// EKRANI GÜNCELLE
	
	SDL_RenderPresent(rend); 

	// Toplam süreyi hesapla
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
