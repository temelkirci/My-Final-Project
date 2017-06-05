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

	Uint32 deltaclock;
	
	Uint32 currentFPS;
	Uint32 oldFPS;
	SDL_Rect viewport;
	int world_x;
	int world_y;
	int world_w;
	int world_h;
	
private:
	Uint32 start;
	
};