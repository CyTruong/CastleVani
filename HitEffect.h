#pragma once
#include "GameObject.h"
#include "Effect.h"

#define HIT_EFF_CD 300

class HitEffect :
	public CGameObject
{
private :
	int timer;
public:
	HitEffect();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~HitEffect();
};

