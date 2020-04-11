#pragma once
#include "GameObject.h"
#include "debug.h"
#define LAMP_BBOX_WIDTH 16
#define LAMP_BBOX_HEIGHT 32

#define LAMP_ANI_IDLE 0

#define LAMP_STATE_DESTROY -1
class Lamp : public CGameObject
{
public:
	Lamp();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Lamp();
};

