#pragma once
#include "Item.h"
#define BBOX_ORB_WIDTH 16
#define BBOX_ORB_HEIGHT 16
#define ORB_ANI_IDLE 0
class BossOrb :
	public Item
{
public:
	BossOrb();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~BossOrb();
};

