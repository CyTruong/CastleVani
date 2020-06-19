#pragma once
#include "Enemy.h"
#define KNIGHT_SPEED 0.018f

#define KNIGHT_GRAVITY 0.001f
#define KNIGHT_JUMP_SPEED 0.5f


#define KNIGHT_STATE_IDLE 0
#define KNIGHT_STATE_RUN 1

#define KNIGHT_BBOX_WIDTH 16
#define KNIGHT_BBOX_HEIGHT 32

#define KNIGHT_ANI_IDLE_LEFT 0
#define KNIGHT_ANI_IDLE_RIGHT 1
#define KNIGHT_ANI_RUN_LEFT 2
#define KNIGHT_ANI_RUN_RIGHT 3

class Knight : public Enemy
{
private:
	bool start;
	int dir;
public:
	Knight();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Knight();
};

