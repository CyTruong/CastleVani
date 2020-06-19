#pragma once
#include "GameObject.h"
#define BBOX_AXE_WIDTH 15
#define BBOX_AXE_HEIGHT 14

#define AXE_ANI_FLY 0

#define AXE_STATE_IDLE 0

class Axe : public CGameObject
{
public:
	Axe();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Axe();
};

