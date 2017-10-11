#pragma once
#include "Texture.h"
#include "SDL/SDL.h"

using namespace std;
class Render : public Texture 
{
public:
	Render();
	~Render();
	
	void render(SDL_Renderer* , bool);

	double deltaclock;
	
	double currentFPS;
	double oldFPS;
	SDL_Rect viewport;
	SDL_Rect minimap;

	int world_x;
	int world_y;
	int world_w;
	int world_h;
	SDL_Window* win;
private:
	double start;
	
};