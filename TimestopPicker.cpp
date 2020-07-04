#include "TimestopPicker.h"



TimestopPicker::TimestopPicker()
{
	this->state = 0;
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(31);
	this->SetAnimationSet(ani_set);
	this->vy = -0.2f;
}

void TimestopPicker::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_TP_WIDTH;
	bottom = y + BBOX_TP_HEIGHT;
}

void TimestopPicker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Simple fall down
	vy += 0.002f * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


	}
}

void TimestopPicker::Render()
{
	if (state != OBJ_DIE)
		animation_set->at(TP_ANI_IDLE)->Render(x, y);
}


TimestopPicker::~TimestopPicker()
{
}
