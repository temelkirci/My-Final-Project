#pragma once
#include "SDL/SDL.h"
#include <string>
#include "Player.h"
#include "Inventory.h"

class Events : public Player , public Inventory
{
public:
	Events();
	~Events();
	
	void klavye(SDL_Renderer*,int,int);
	//int xpoz;
	//int ypoz;
	char* mevcut_resim;
	char* mevcut_mermi;
	bool pause;
	double bullet_angle;
	
	bool collision;
	SDL_Rect mouse;
	SDL_Rect solid_mouse;
	bool move;
	string drawing;
	bool draw_apply;
	bool yerlestirme;
	int indis_item;
	bool cancel_draw;

	double x_target;
	double y_target;
	double x_distance;
	double y_distance;
	double tanjant_angle;
	double tanjant;

	bool player_inf;
	string current_cursor;
private:
	
	SDL_Event tus ;
};

