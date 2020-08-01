#pragma once
#include "GameObject.h"
#include "Effect.h"

class DestroyEffect :
	public CGameObject
{
public:
	DestroyEffect();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~DestroyEffect();
};

