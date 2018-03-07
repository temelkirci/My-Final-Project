#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

class GameObject
{
public:
	GameObject(); // Default Constructor
	GameObject(const GameObject &pObj);
	GameObject& operator = (const GameObject& pObj);
	~GameObject();

	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Update() final;
	virtual void Clean() final;

	static GameObject* getInstanceGameObject();
protected:
	static GameObject* mInstanceGameObject;
};