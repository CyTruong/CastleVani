#pragma once
#include "Item.h"
#define BBOX_TP_WIDTH 16
#define BBOX_TP_HEIGHT 16
#define TP_ANI_IDLE 0
class TimestopPicker :
	public Item
{
public:
	TimestopPicker();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~TimestopPicker();
};

