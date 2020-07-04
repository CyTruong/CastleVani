#pragma once
#include "Enemy.h"

#define SKELETON_SPEED 0.04f

#define SKELETON_GRAVITY 0.001f
#define SKELETON_JUMP_SPEED 0.5f
#define SKELETON_STATE_RUN 0

#define SKELETON_BBOX_WIDTH 16
#define SKELETON_BBOX_HEIGHT 32

#define SKELETON_ANI_RUN_LEFT 0
#define SKELETON_ANI_RUN_RIGHT 1
class Skeleton :
	public Enemy
{
private:
	bool start;
	int dir;
	long atkinterval;
public:
	Skeleton();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	void ThrowBone();
	~Skeleton();
};

