#pragma once
#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include "GameObjects.h"
#include "Sounds.h"

using namespace std;

class Events : public GameObjects , public Sounds
{
public:
	Events();
	~Events();
	
	void event(SDL_Renderer* pRenderer);

private:
	char* mCurrentPlayerImage;
	char* mCurrentBullet;
	bool mPauseGame;
	double mAngleBullet;

	bool mIsCollision;
	bool mIsMove;
	string mDrawing;
	bool mApplyDraw;
	bool mPlacement;
	int mIndexItem;
	bool mCancelDraw;

	double mTargetX;
	double mTargetY;
	double mDistanceX;
	double mDistanceY;
	double mTangentAngle;
	double mTangent;

	SDL_Event mKey;
};

