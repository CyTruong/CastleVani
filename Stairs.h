#pragma once
#include "GameObject.h"
#define STAIRS_BBOX_WIDTH  3
#define STAIRS_BBOX_HEIGHT 16
#define STAIRS_L2R 1
#define STAIRS_R2L 2
class Stairs : public CGameObject
{
public :
	int width;
	int height;
public:
	int type;
public:
	Stairs(float l,float t, float r,float b,int type);
	virtual void Render();
	virtual void SetSimonPos(float &x, float &y,int width,int height);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetStaireVector(float vy,float& dx, float& dy);
	~Stairs();
};

