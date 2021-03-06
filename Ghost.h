#pragma once
#include "Enemy.h"
#define GHOST_SPEED 0.025f
#define GHOST_BBOX_WIDTH 16
#define GHOST_BBOX_HEIGHT 16
#define GHOST_ANI_LEFT 0
#define GHOST_ANI_RIGHT 1
#define GHOST_MECH_1 0
#define GHOST_MECH_2 1

class Ghost : public Enemy
{
private:
	float dirX, dirY;
	int mech;
	float tempX, tempY;
public:
	Ghost();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Ghost();
};

