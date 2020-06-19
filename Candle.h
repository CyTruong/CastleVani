#pragma once
#include "GameObject.h"
#define CANDLE_BBOX_WIDTH 8
#define CANDLE_BBOX_HEIGHT 16

#define CANDLE_ANI_IDLE 0

#define CANDLE_STATE_DESTROY -1
class Candle :
	public CGameObject
{
public:
	Candle();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Candle();
};

