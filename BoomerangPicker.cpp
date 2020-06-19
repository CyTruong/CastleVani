#include "BoomerangPicker.h"



BoomerangPicker::BoomerangPicker()
{
	this->state = 0;
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(12);

	this->SetAnimationSet(ani_set);
	this->vy = -0.2f;
}

void BoomerangPicker::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_BMR_WIDTH;
	bottom = y + BBOX_BMR_HEIGHT;
}

void BoomerangPicker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Simple fall down
	vy += 0.002f * dt;
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

void BoomerangPicker::Render()
{
	if (state != OBJ_DIE)
		animation_set->at(BMR_ANI_IDLE)->Render(x, y);
}


BoomerangPicker::~BoomerangPicker()
{
}
