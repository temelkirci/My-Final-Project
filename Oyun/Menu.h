#pragma once
#include "SDL/SDL.h"
#include <map>
#include <string>
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
using namespace std;

class Menu 
{
public:
	Menu();
	~Menu();

	void menu_yukle(char* , SDL_Renderer*);
	void menu_goster(SDL_Renderer* , int , int , int , int);
	bool loadPathMenu(char* , string , SDL_Renderer*);
	bool klavye_mouse(bool);
	void loadMenu(SDL_Renderer*);
	
	TTF_Font* menu_font;
	Mix_Chunk* click_x;
	Mix_Music* back;
	
	SDL_Rect menü_mouse;

	SDL_Color menu_color;
	SDL_Color text_color;

	char* button_array[5];
	SDL_Rect start_button; //
	SDL_Rect resume_button;
	SDL_Rect credits_button; //
	SDL_Rect save_button; //
	SDL_Rect exit_button; //
	SDL_Rect load_button; //

	map<string , SDL_Texture*> map_button;

private:
	SDL_Texture* menu_texture;
	SDL_Surface* menu_surface;

	SDL_Texture* texture_buttons;
	SDL_Surface* surface_buttons;

	SDL_Event ev ;
};