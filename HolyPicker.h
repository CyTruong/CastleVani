#pragma once
#include "Item.h"
#define BBOX_DAGGER_WIDTH 16
#define BBOX_DAGGER_HEIGHT 16
#define DAGGER_ANI_IDLE 0
class HolyPicker : public Item
{
public:
	HolyPicker();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~HolyPicker();
};
