#include "WhipUpdate.h"



WhipUpdate::WhipUpdate()
{ 
	this->state = 0;
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(5);

	this->SetAnimationSet(ani_set);
	this->vy = -0.2f;
}

void WhipUpdate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_WHIP_WIDTH;
	bottom = y + BBOX_WHIP_HEIGHT;
}

void WhipUpdate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void WhipUpdate::Render()
{
	if (state != OBJ_DIE)
		animation_set->at(WHIP_ANI_IDLE)->Render(x, y);
}


WhipUpdate::~WhipUpdate()
{
}
