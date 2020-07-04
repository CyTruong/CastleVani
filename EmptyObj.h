#pragma once
#include "GameObject.h"

class EmptyObj : public CGameObject
{
public:
	EmptyObj();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~EmptyObj();
};

