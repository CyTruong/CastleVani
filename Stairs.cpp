#include "Stairs.h"


Stairs::Stairs(float l, float t, float r, float b,int type)
{
	this->x = l;
	this->y = t;
	this->width = r - l +1;
	this->height = b - t + 1;
	collision_able = false;
	atk_able = false;
	this->type = type;
}

void Stairs::Render()
{
	RenderBoundingBox();
}

void Stairs::SetSimonPos(float & x, float & y,int width, int height)
{
	float x1, x2, y1, y2;
	if (type == STAIRS_L2R) {
		GetBoundingBox(x1, y2, x2, y1);
	}
	else {
		GetBoundingBox(x2, y2, x1, y1);
	}
	float vABx = x2 - x1;
	float vABy = y2 - y1;
	if (type == STAIRS_L2R) {
		x = ((vABx*(y - y1)) / vABy) + x1 - 2.2*width;
	}
	else {
		x = ((vABx*(y - y1)) / vABy) + x1 + 2.2*width;
	}

}




void Stairs::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void Stairs::GetStaireVector(float SimonX, float SimonY,float& vx, float& vy, float & dx, float & dy)
{
	float l, t, r, b;
	GetBoundingBox(l,t,r,b);


	if (vy == 0) {
		vx = 0;
		vy = 0;
		dx = 0;
		dy = 0;
		return;
	}
	//speed = 0.05 * cos45
	if (type == STAIRS_L2R) {
		if (vy > 0) {
			dy = 0.03f;
			dx = (l - r)*dy / (b - t);
		}
		if (vy < 0) {
			dy = -0.03;
			dx = (r - l)*dy / (t - b);
		}
	}
	if (type == STAIRS_R2L) {
		if (vy > 0) {
			dy = 0.03f;
			dx = (r - l)*dy / (b - t);
		}
		if (vy < 0) {
			dy = -0.03f;
			dx = (l - r)*dy / (t - b);
		}
	}
	
	if (dx > 0) {
		vx = 0.05;
	}
	else {
		vx = -0.05f;
	}
	vy = (dy / dx)*vx;
	

}


Stairs::~Stairs()
{
}
