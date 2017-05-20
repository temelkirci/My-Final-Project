#pragma once
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Render.h"
#include "Menu.h"

class Game : public Render , public Menu
{
public:
	Game(); // Yapýcý fonksiyon
	~Game();  // Yýkýcý fonksiyon

	// FONKSÝYONLAR

	bool init(const char*,int,int,int,int,int);
	SDL_Renderer* renderer;
	Mix_Music *back;

private:
	// DEÐÝÞKENLER
	
	SDL_Window* pencere ;
	SDL_Texture* texture;
	SDL_Surface* surface;
};
