#pragma once
#define BBOX_MONEYBAB_WIDTH 16
#define BBOX_MONEYBAB_HEIGHT 16
#define MONEYBAB_ANI_IDLE 0

#include "Item.h"
class MoneyBag :
	public Item
{
public:
	MoneyBag();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~MoneyBag();
};

