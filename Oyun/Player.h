#pragma once
#include <SDL/SDL.h>
#include <string>
#include <map>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <iostream>
#include "Timer.h"

using namespace std;
const int MAX_HEALTH = 100;

class Player : public Timer
{
public:
	Player();
	Player(const Player& pPlayer);
	Player& operator = (const Player& pPlayer);
	~Player();

	bool loadPlayerWeapon(char* , SDL_Renderer* pRenderer, char*);
	void drawPlayer(SDL_Renderer* pRenderer, int pCameraX , int pCameraY);
	void updatePLayer(SDL_Renderer* pRenderer, Uint32);
	void loadPlayer(SDL_Renderer* pRenderer);
	void playerInformation(SDL_Renderer* pRenderer);
	void deathInformation(SDL_Renderer*pRenderer);

	// get fonksiyonlar�
	const int getPlayerHealth();
	SDL_Rect getPlayerPosition();
	int getPlayerThirsty();
	int getPlayerHunger();
	int getPlayerAttackPower();

	double getPlayerSpeed();
	double getPlayerXPos();
	double getPlayerYPos();

protected:
	double mPlayerPositionX;
	double mPlayerPositionY;

	double mPlayerAngle;
	double mPlayerSpeed;

	string mPlayerDirection;
private:

	Uint32 pTime;
	Uint32 mPlayerTime;
	Uint32 mPlayerHungerTime;
	Uint32 mPlayerThirstyTime;
	Uint32 mPlayerHealthTime;

	// Karakterin mouse ile t�klanan yere gidece�i koordinatlar
	int mPlayerTargetX;
	int mPlayerTargetY;


	// Karakterin a�l�k , susuzluk , sa�l�k ve sald�r� g�c� bilgileri
	int mPlayerThirsty;
	int mPlayerHunger;
	int mPlayerAttackPower;
	int mPlayerHealth;

	// Karakterin mermi say�lar�
	int mPlayerHandgunBullet;
	int mPlayerRifleBullet;
	int mPlayerShotgunBullet;

	// Karakterin eksenlere g�re h�zlar�
	double mPlayerPositiveSpeedX;
	double mPlayerPositiveSpeedY;
	double mPlayerNegativeSpeedX;
	double mPlayerNegativeSpeedY;

	string mBulletDirection;
	string mPlayerStatus;
	string mPlayerGun;

	SDL_Texture* mPlayerDeadTexture;
	SDL_Rect mPlayerDeadRect;
	
	//�ld�kten sonra ekranda g�sterilecek bilgiler
	int mTotalSurvivalDay; // hayatta kal�nan g�n say�s�
	int mNumberMeteor; // Par�alanm�� meteor say�s�
	int mLastThirsty; // �lmeden �nceki susuzluk miktar�
	int mLastHunger; // �lmeden �nceki a�l�k miktar�
	Uint32 mTotalGameDuration; // toplam oyun s�resi (dakika cinsinden)

	int mKnifeTime;

	TTF_Font* mPlayerFont;
	string mPlayerWeapon;
	SDL_Color mPlayerColor;
	SDL_Rect mInformationRect;
	SDL_Rect mPlayerRect;
	SDL_Texture* mPlayerTexture;
	SDL_Point mPlayerPoint;
	map<string , SDL_Texture*> mPLayerWeaponMap;
};
