#pragma once
#include "Enemy.h"
#define MONKEY_SPEED 0.12f
#define MONKEY_SPEED2 0.1f

#define MONKEY_GRAVITY 0.0005f
#define MONKEY_JUMP_SPEED 0.07f
#define MONKEY_JUMP_SPEED2 0.2f

#define MONKEY_STATE_IDLE 0
#define MONKEY_STATE_JUMP 1

#define MONKEY_BBOX_WIDTH 16
#define MONKEY_BBOX_HEIGHT 16

#define MONKEY_ANI_LEFT 0
#define MONKEY_ANI_RIGHT 1

#define MAX_HIGHT 180


class Monkey :
	public Enemy
{
private:
	bool start;
	int dir;
	bool isJumping;
	long timer;
	int counter;
	float curspeed, curhight;
	int jumpstate;
public:
	Monkey();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~Monkey();
};

