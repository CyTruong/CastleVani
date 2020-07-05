#pragma once
#include "Enemy.h"
#define WOFT_SPEED 0.12f

#define WOFT_GRAVITY 0.002f
#define WOFT_JUMP_SPEED 0.35f


#define WOFT_STATE_IDLE 0
#define WOFT_STATE_RUN 1
#define WOFT_STATE_JUMP 2

#define WOFT_BBOX_WIDTH 32
#define WOFT_BBOX_HEIGHT 16

#define WOFT_ANI_IDLE_LEFT 0
#define WOFT_ANI_IDLE_RIGHT 1
#define WOFT_ANI_JUMP_LEFT 2
#define WOFT_ANI_JUMP_RIGHT 3
#define WOFT_ANI_RUN_LEFT 4
#define WOFT_ANI_RUN_RIGHT 5

class Woft : public Enemy
{
private :
	bool start;
	int dir;
	bool isJumped;
public:
	Woft();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Woft();
};

