#pragma once
#include "GameObject.h"
#define BBOX_BMR_WIDTH 16
#define BBOX_BMR_HEIGHT 9


class Boomerang :
	public CGameObject
{
private : 
	bool isback;
public:
	Boomerang();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Boomerang();
};

