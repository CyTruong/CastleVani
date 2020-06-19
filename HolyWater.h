#pragma once
#include "GameObject.h"
#define BBOX_HOLYWT_WIDTH 10
#define BBOX_HOLYWT_HEIGHT 8

#define HOLY_ANI_FLY_LEFT 0
#define HOLY_ANI_FLY_RIGHT 1
#define HOLY_ANI_DFESTROY 2

#define HOLY_STATE_IDLE 0
#define HOLY_STATE_DESTROY -1

class HolyWater : public CGameObject
{
public:
	HolyWater();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~HolyWater();
};
