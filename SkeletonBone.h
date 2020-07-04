#pragma once
#pragma once
#include "Enemy.h"

#define BONE_SPEED 0.04f
#define BONE_GRAVITY 0.001f
#define BONE_STATE_IDLE 0

#define BONE_BBOX_WIDTH 16
#define BONE_BBOX_HEIGHT 16

#define BONE_ANI_IDLE_LEFT 0
#define BONE_ANI_IDLE_RIGHT 1
class SkeletonBone : public Enemy
{
public:
	SkeletonBone();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual Enemy* clone();
	~SkeletonBone();
};

