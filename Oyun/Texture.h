#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"
#include <tuple>

using namespace std;

class Texture : public GameObject
{
public:
	Texture();
	~Texture();

	void load_textures(SDL_Renderer*);
	void arkaplan_yükle(char* , SDL_Renderer*);
	bool load(char* , string , SDL_Renderer*);
	void item_bilgi(SDL_Renderer* , string);
	void draw_object(SDL_Renderer* , Uint32); 
	void draw_texture(SDL_Renderer*); 
	void draw_solid_texture(SDL_Renderer*);
	void draw_camera(SDL_Renderer* , double , double , int , int);
	void draw_bullet(SDL_Renderer* , double , double);

	bool randomPosition(int , int , Item&);
	void tank(SDL_Renderer*, int, int);

private:
	map<string, SDL_Texture*> map_texture; // ilk deðiþken string , ikinci deðiþken Texture tutan bir deðiþken
	SDL_Surface* load_surface;
	SDL_Rect camera;
	SDL_Surface* sur_bck;
	SDL_Surface* surface_background;
	SDL_Texture* load_texture;
	bool object_collision;
	string mevcut_mermi;
	int z;
	int map_row;
	int map_column;
	int map_x;
	int map_y;

	int miniMap_x;
	int miniMap_y;
	int miniMap_w;
	int miniMap_h;

	SDL_Rect map;
};
