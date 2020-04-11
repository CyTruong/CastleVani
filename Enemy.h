#pragma once
#include "GameObject.h"
class Enemy : public CGameObject
{
public:
	bool isFree;
public:
	Enemy();
	virtual Enemy* clone();
	~Enemy();
};

