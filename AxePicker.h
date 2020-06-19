#pragma once
#include "Item.h"
#define BBOX_AXE_WIDTH 16
#define BBOX_AXE_HEIGHT 16
#define AXE_ANI_IDLE 0
class AxePicker : public Item
{
public:
	AxePicker();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~AxePicker();
};

