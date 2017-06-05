#include <iostream>
#include "SDL/SDL.h"
#include <string>
#include "Window.h"

using namespace std;

Window :: Window()
{
	x_window = 0;
	y_window = 250;
	w_window = 200;
	h_window = 350;

	x_crafting = 1100;
	y_crafting = 300;
	w_crafting = 250;
	h_crafting = 150;

	slot1_rect.x = 546;
	slot1_rect.y = 120;
	slot1_rect.w = 50;
	slot1_rect.h = 50;

	slot2_rect.x = 630;
	slot2_rect.y = 120;
	slot2_rect.w = 50;
	slot2_rect.h = 50;

	final_rect.x = 750;
	final_rect.y = 110;
	final_rect.w = 70;
	final_rect.h = 70;

	statu_inventory = false;
	statu_crafting = false;

}

Window :: ~Window()
{

}

void Window :: information_window(SDL_Renderer* render, Uint32 menü_time)
{
	SDL_Rect window_menü;
	window_menü.x = x_window;
	window_menü.y = y_window;
	window_menü.w = w_window;
	window_menü.h = h_window;

	SDL_RenderCopyEx(render , window_texture , NULL , &window_menü , 0 , 0 , SDL_FLIP_NONE);
}

void Window :: crafting(SDL_Renderer* rend)
{
	crafting_coord.x = 525;
	crafting_coord.y = 50;
	crafting_coord.w = 300;
	crafting_coord.h = 180;

	SDL_RenderCopyEx(rend , crafting_texture , NULL , &crafting_coord , 0 , 0 , SDL_FLIP_NONE);

	if(get<2>(Slot1))
	{
		SDL_RenderCopyEx(rend , get<1>(Slot1) , NULL , &slot1_rect , 0 , 0 , SDL_FLIP_NONE);
	}

	if(get<2>(Slot2))
	{
		SDL_RenderCopyEx(rend , get<1>(Slot2) , NULL , &slot2_rect , 0 , 0 , SDL_FLIP_NONE);
	}

	if(get<2>(Slot1) || get<2>(Slot2))
	{
		if((get<0>(Slot2) == "rock_1" || get<0>(Slot1) == "rock_1") && (get<3>(Slot1) == 1))
		{
			get<0>(finalSlot) = "brick_block";
			get<1>(finalSlot) = all_textures["brick_block"];
			get<2>(finalSlot) = true;
			get<3>(finalSlot) = 2;
			SDL_RenderCopyEx(rend , get<1>(finalSlot) , NULL , &final_rect , 0 , 0 , SDL_FLIP_NONE);
		}

		else if((get<0>(Slot2) == "stone" || get<0>(Slot1) == "stone") && (get<3>(Slot1) == 1))
		{
			get<0>(finalSlot) = "stone_block";
			get<1>(finalSlot) = all_textures["stone_block"];
			get<2>(finalSlot) = true;
			get<3>(finalSlot) = 2;
			SDL_RenderCopyEx(rend , get<1>(finalSlot) , NULL , &final_rect , 0 , 0 , SDL_FLIP_NONE);
		}

		else if((get<0>(Slot2) == "wood" || get<0>(Slot1) == "wood") && (get<3>(Slot1) == 1))
		{
			get<0>(finalSlot) = "wood_block";
			get<1>(finalSlot) = all_textures["wood_block"];
			get<2>(finalSlot) = true;
			get<3>(finalSlot) = 2;
			SDL_RenderCopyEx(rend , get<1>(finalSlot) , NULL , &final_rect , 0 , 0 , SDL_FLIP_NONE);
		}

		else if((get<0>(Slot2) == "iron" || get<0>(Slot1) == "iron") && (get<3>(Slot1) == 1))
		{
			get<0>(finalSlot) = "iron_block";
			get<1>(finalSlot) = all_textures["iron_block"];
			get<2>(finalSlot) = true;
			get<3>(finalSlot) = 2;
			SDL_RenderCopyEx(rend , get<1>(finalSlot) , NULL , &final_rect , 0 , 0 , SDL_FLIP_NONE);
		}

		else if((get<0>(Slot2) == "steel" || get<0>(Slot1) == "steel") && (get<3>(Slot1) == 1))
		{
			get<0>(finalSlot) = "steel_block";
			get<1>(finalSlot) = all_textures["steel_block"];
			get<2>(finalSlot) = true;
			get<3>(finalSlot) = 2;
			SDL_RenderCopyEx(rend , get<1>(finalSlot) , NULL , &final_rect , 0 , 0 , SDL_FLIP_NONE);
		}
	}
}

void Window :: load_inf(SDL_Renderer* ren)
{
	SDL_Surface* surface_cr = IMG_Load("assets/crafting.png");
	SDL_Texture* texture_cr = SDL_CreateTextureFromSurface(ren , surface_cr);	// yüzeyi renderleyerek texture oluþtur	
	SDL_FreeSurface(surface_cr);
	
	crafting_texture = texture_cr;
}

