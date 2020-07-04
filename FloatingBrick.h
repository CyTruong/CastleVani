#pragma once
#include "GameObject.h"
#include "debug.h"
#define LB_BBOX_WIDTH 32
#define LB_BBOX_HEIGHT 8
#define LB_ANI_IDLE 0
#define LB_SPEED 0.01f

class FloatingBrick : public CGameObject
{
private :
	float from, to;
	int dir;
public:
	FloatingBrick(float from,float to);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~FloatingBrick();
};

