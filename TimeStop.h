#pragma once
#include "GameObject.h"
class TimeStop : public CGameObject
{
private :
	long timecount;
public:
	TimeStop();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~TimeStop();
};

