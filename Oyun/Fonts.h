#pragma once
#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <string.h>
#include "Sounds.h"
#include <map>
using namespace std;

class Fonts : public Sounds
{
public:

	Fonts();
	~Fonts();

	void load_Resim(SDL_Renderer*);
	int Resim(char* , string , SDL_Renderer*);
	void barbaros_status(SDL_Renderer* , int , int , int , int , int , int , int , int);
	void Write_Text(SDL_Renderer* , Uint32 , char*);
	TTF_Font* Font ;
	
	SDL_Texture* degerTexture;

	SDL_Color backColor; // arkaplan beyaz olacak

	SDL_Rect backRect;
	SDL_Rect hungerRect; // 0-100 piksel arasýnda olacak
	SDL_Rect thirstyRect; // 0-100 piksel arasýnda olacak
	SDL_Rect healthRect; // 0-100 piksel arasýnda olacak

	double total; 

	SDL_Texture* resim_texture;
	SDL_Surface* resim_surface;
	map<string , SDL_Texture*> resim_map;
	SDL_Rect arkaPlan;
private:

	Uint32 toplam;	
	char* dizi[4];
};