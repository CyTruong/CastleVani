#pragma once
#include "Enemy.h"

#define ZOMBIE_SPEED 0.02f;
#define ZOMBIE_BBOX_WIDTH 16
#define ZOMBIE_BBOX_HEIGHT 32

#define ZOMBIE_ANI_RUN_LEFT 0
#define ZOMBIE_ANI_RUN_R 1

class Zombie : public Enemy
{
public:
	Zombie();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Zombie();
};

