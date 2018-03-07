#pragma once
#include <SDL/SDL.h>
#include <string>
#include <map>
#include "GameObject.h"
#include <SDL/SDL_image.h>
#include <iostream>

using namespace std;
const int MAX_HEALTH = 100;

class Player : public GameObject 
{
public:
	Player();
	~Player();

	bool loadPlayerWeapon(char* , SDL_Renderer* pRenderer, char*);
	void drawPlayer(SDL_Renderer* pRenderer, string , double , double , double , double , string , Uint32);
	void updatePLayer(SDL_Renderer* pRenderer, Uint32);
	void loadPlayer(SDL_Renderer* pRenderer);
	void playerInformation(SDL_Renderer* pRenderer);
	void deathInformation(SDL_Renderer*pRenderer);

	
private:
	Uint32 player_time;
	Uint32 hunger_time;
	Uint32 thirsty_time;

	int x_hedef;
	int y_hedef;

	int thirtsy;
	int hunger;
	int attack_power;
	int health;

	int handgun_mermi;
	int rifle_mermi;
	int shotgun_mermi;

	bool oyun_baslat;
	bool trex_attack;

	double mPlayerPositiveSpeedX;
	double mPlayerPositiveSpeedY;
	double mPlayerNegativeSpeedX;
	double mPlayerNegativeSpeedY;

	string direction_bullet;
	string barbaros_durum;
	string barbaros_guns;

	double xpoz;
	double ypoz;
	double mPlayerAngle;
	double mPlayerSpeed;

	bool active_bullet;
	SDL_Texture* dead_texture;
	SDL_Rect death_rect;
	Uint32 health_time;
	//

	int total_survival_day; // hayatta kalýnan gün sayýsý
	int number_trex; // öldürülen t-rex sayýsý
	int number_meteor; // parçalanmýþ meteor sayýsý
	int last_thirtsy; // susuzluk miktarý
	int last_hunger; // açlýk miktarý
	Uint32 total_game_time; // toplam oyun süresi (dakika cinsinden)

							//
	int mKnifeTime;
	Uint32 trex_attack_time;

	SDL_Color mPlayerColor;
	SDL_Rect mPlayerRect;
	SDL_Rect mInformationRect;

	SDL_Texture* mPlayerTexture;
	SDL_Point mPlayerPoint;
	map<string , SDL_Texture*> mPLayerWeaponMap;
};
