#pragma once
#include "Enemy.h"
#define dRAVEN_SPEED 0.05f
#define dRAVEN_BBOX_WIDTH 16
#define dRAVEN_BBOX_HEIGHT 16
#define dRAVEN_STATE_IDLE 0
#define dRAVEN_STATE_FLY	1
#define dRAVEN_ANI_IDLE_LEFT 0
#define dRAVEN_ANI_IDLE_RIGHT 1
#define dRAVEN_ANI_FLY_LEFT 2
#define dRAVEN_ANI_FLY_RIGHT 3

class dRaven :
	public Enemy
{
private:
	float dirX, dirY;
	long timer;
public:
	dRaven();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~dRaven();
};

