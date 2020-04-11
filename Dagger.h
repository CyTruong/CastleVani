#pragma once
#include "GameObject.h"
#define BBOX_DAGGER_WIDTH 16
#define BBOX_DAGGER_HEIGHT 9

#define DAGGER_ANI_FLY_LEFT 0
#define DAGGER_ANI_FLY_RIGHT 1
class Dagger : public CGameObject
{
public:
	Dagger();
	void Update();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Dagger();
};

