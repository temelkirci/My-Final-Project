#pragma once

#include <SDL.h>

class GameObject
{
public:
	GameObject();

	virtual void draw(SDL_Renderer*) = 0;
	virtual void update() = 0;

	void setPosition(int , int);
protected:
	float x , y;
};