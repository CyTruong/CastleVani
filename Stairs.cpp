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




void Stairs::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void Stairs::GetStaireVector(float vy, float & dx, float & dy)
{
	float l, t, r, b;
	GetBoundingBox(l,t,r,b);
	if (vy == 0) {
		dx = 0;
		dy = 0;
		return;
	}
	if (type==STAIRS_L2R) {
		if (vy > 0) {
			dy = 0.1f;
			dx =  (l -r )*dy / ( b - t);
		}
		if (vy < 0) {
			dy = -0.1;
			dx = (r - l )*dy / (t - b);
		}
	}
	if (type==STAIRS_R2L) {
		if (vy > 0) {
			dy = 0.1f;
			dx = (r - l)*dy / (b-t);
		}
		if (vy < 0) {
			dy = -0.1f;
			dx = (l - r)*dy / (t-b);
		}
	}

}


Stairs::~Stairs()
{
}
