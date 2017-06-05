#pragma once
#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include <map>
#include <tuple>
#include "Fonts.h"

using namespace std;

class Inventory : public Fonts 
{
public:
	Inventory();
	~Inventory();

	void Envanter_Yukle(string , string , SDL_Renderer*);
	void Envanter_Çiz(string , int , int , int , int , SDL_Renderer*);
	void Envanter_Güncelle(SDL_Renderer*);

	void Esya_Ekle(string , int , SDL_Renderer* , SDL_Texture*);
	
	int inventory_size; // envanterdeki farklý eþya sayýsý

	SDL_Color inventory_color;

	tuple<string , // eþyanýn adý
		SDL_Texture* , // eþya texture
		int, // eþya sayýsý
		int , // esya çizim koordinatý x ekseni
		int> // esya çizim koordinatý y ekseni
	envanter[18];
	
	map<string , SDL_Texture*> envanter_draw;
	string envanter_durum ;
	int max_envanter; // envanterin maksimum kapasitesi
	SDL_Rect rect_inventory;
private:
	SDL_Texture* envanter_texture; // envanter resmi
	SDL_Texture* adet_texture;
};