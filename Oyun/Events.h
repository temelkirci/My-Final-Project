#pragma once
#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include "Core.h"

class Events : public Core
{
public:
	Events();
	~Events();
	
	void mEvent(SDL_Renderer* , double , double);
	
private:
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

	double playerAngle;

	bool player_inf;
	string current_cursor;
	SDL_Event tus ;
};

