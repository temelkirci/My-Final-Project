#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <map>
#include <string>
#include <SDL/SDL_image.h>
#include <iostream>
#include <ctime>
#include "GameObject.h"

using namespace std;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(const Enemy& pEnemy);
	Enemy& operator = (const Enemy& pEnemy);
	~Enemy();

	void drawAirplane(SDL_Renderer* pRenderer, int , int , Uint32);
	void drawCreature(SDL_Renderer* pRenderer, int , int , SDL_Rect , Uint32);

	void loadEnemy(SDL_Renderer* pRenderer);
	void loadEnemyItems(char* mPathFile, char* , SDL_Renderer* pRenderer);
	
	static Enemy* getInstanceEnemy();
private:
	static Enemy* mInstanceEnemy;

	map<string , SDL_Texture*> mEnemyMap;
	Uint32 mAirplaneTime;
	SDL_Rect mAirplaneRect;

	Uint32 mCreatureTime;
	SDL_Rect mCreatureRect;
	Uint32 mMoveTime;

	int mCreatureHealth;
};