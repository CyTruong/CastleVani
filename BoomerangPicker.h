#pragma once
#include "Item.h"
#define BBOX_BMR_WIDTH 16
#define BBOX_BMR_HEIGHT 16
#define BMR_ANI_IDLE 0
class BoomerangPicker :
	public Item
{
public:
	BoomerangPicker();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~BoomerangPicker();
};

