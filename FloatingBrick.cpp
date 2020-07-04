#include "FloatingBrick.h"



FloatingBrick::FloatingBrick(float from,float to)
{
	this->from = from;
	this->to = to;
	this->collision_able = true;
	this->atk_able = false;
	vx = LB_SPEED;
}

void FloatingBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + LB_BBOX_WIDTH;
	bottom = y + LB_BBOX_HEIGHT;

}

void FloatingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt,coObjects);
	if (vx > 0 && x + LB_BBOX_WIDTH >= to) {
		vx = -LB_SPEED;
	}
	if (vx < 0 && x < from) {
		vx = LB_SPEED;
	}
	x += dx;
	y += dy;
}

void FloatingBrick::Render()
{
	animation_set->at(LB_ANI_IDLE)->Render(x, y);

}


FloatingBrick::~FloatingBrick()
{
}
