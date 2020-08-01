#pragma once
#include "GameObject.h"
#include "Stairs.h"
#define STAIRS_BBOX_WIDTH  16
#define STAIRS_BBOX_HEIGHT 32
#define STAIRS_L2R 1
#define STAIRS_R2L 2
#define STAIRS_POS_BOT 1
#define STAIRS_POS_TOP 2
#define SIMON_HAFT_BBOX_WIDTH 8
class StairStep :
	public CGameObject
{
public:
	LPGAMEOBJECT Stair;
public:
	int width;
	int height;
public:
	StairStep(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual bool GetSimonVertex(float simonX, float simonY, float &vx, float &vy);
	~StairStep();
};

