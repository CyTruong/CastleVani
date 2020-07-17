#pragma once
#include "Item.h"
#define BBOX_HEART_WIDTH 8
#define BBOX_HEART_HEIGHT 8
#define HEART_ANI_IDLE 0
class HeartMini :
	public Item
{
public:
	HeartMini();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~HeartMini();
};

