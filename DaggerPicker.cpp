#include "DaggerPicker.h"



DaggerPicker::DaggerPicker()
{
	this->state = 0;
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(6);

	this->SetAnimationSet(ani_set);
	this->vy = -0.2f;
}

void DaggerPicker::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_DAGGER_WIDTH;
	bottom = y + BBOX_DAGGER_HEIGHT;
}

void DaggerPicker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void DaggerPicker::Render()
{
	if (state != OBJ_DIE)
		animation_set->at(DAGGER_ANI_IDLE)->Render(x, y);
}


DaggerPicker::~DaggerPicker()
{
}
