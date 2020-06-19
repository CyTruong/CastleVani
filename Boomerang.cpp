#include "Boomerang.h"



Boomerang::Boomerang()
{
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(13);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 0;
	this->y = 0;
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_BMR_WIDTH;
	bottom = y + BBOX_BMR_HEIGHT;
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
}

void Boomerang::Render()
{
	animation_set->at(0)->Render(x, y);

}


Boomerang::~Boomerang()
{
}
