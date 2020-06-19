#pragma once
#include "Enemy.h"
#define BAT_SPEED 0.04f
#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 12
#define BAT_ANI_IDLE 0
#define BAT_ANI_LEFT 1
#define BAT_ANI_RIGHT 2

class Bat : public Enemy
{
private:
	float dirX, dirY;
public:
	Bat();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Bat();
};

