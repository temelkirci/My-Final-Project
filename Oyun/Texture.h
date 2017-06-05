#pragma once
#include <SDL/SDL.h>
#include <string>
#include <map>
#include "Events.h"
#include <tuple>

using namespace std;

class Texture : public Events
{
public:
	Texture();
	~Texture();

	void load_textures(SDL_Renderer*);
	void arkaplan_yükle(string , SDL_Renderer*);
	bool load(string , string , SDL_Renderer*);
	void item_bilgi(SDL_Renderer* , string);
	void draw_object(SDL_Renderer* , Uint32); 
	void draw_texture(SDL_Renderer*); 
	void draw_solid_texture(SDL_Renderer*);
	void draw_camera(SDL_Renderer* , int* ,int* ,int ,int);
	void draw_bullet(SDL_Renderer*);

	map<string , SDL_Texture*> map_texture; // ilk deðiþken string , ikinci deðiþken Texture tutan bir deðiþken
	SDL_Surface* load_surface;
	SDL_Rect camera;
	SDL_Surface* sur_bck;
	int mermi_x;
	int mermi_y;
	string mevcut_mermi;
	int z;
	int map_row;
	int map_column;
	int map_x;
	int map_y;

	SDL_Rect map;
private:
	SDL_Surface* surface_background;
	SDL_Texture* load_texture;
	bool object_collision;
};
