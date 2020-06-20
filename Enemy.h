#pragma once
#include "GameObject.h"
#include "Utils.h"
class Enemy : public CGameObject
{
public:
	bool isFree;
	LPGAMEOBJECT player;
	int Hp;
public:
	Enemy();
	virtual Enemy* clone();
	virtual bool minusHp(int dam) {
		Hp = Hp - dam;
		if (Hp<=0) {
			return true;
		}
		return false;
	}
	~Enemy();
};

