#include "HolyWater.h"
#include "Utils.h"


HolyWater::HolyWater()
{
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(9);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 0;
	this->y = 800;
	this->state = HOLY_STATE_IDLE;
}



void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_HOLYWT_WIDTH;
	bottom = y + BBOX_HOLYWT_HEIGHT;
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (state!=HOLY_STATE_DESTROY && vx!=0) {
		vy += 0.008f;
		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents,false,true);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else {
			state = HOLY_STATE_DESTROY;
		}
	}


}

void HolyWater::Render()
{
	int ani = 0;
	if (state == HOLY_STATE_IDLE) {
		ani = HOLY_ANI_FLY_LEFT;
		if (vx > 0) {
			ani = HOLY_ANI_FLY_RIGHT;
		}
	}
	if (state == HOLY_STATE_DESTROY) {
		ani = HOLY_ANI_DFESTROY;
	}
	
	bool islast = animation_set->at(ani)->Render(x, y);
	if (islast && state==HOLY_STATE_DESTROY) {
		this->x = 0;
		this->y = 800;
		this->vx = 0;
		this->vy = 0;
		state = HOLY_STATE_IDLE;
		
		DebugOut(L"Hody destroyes\n");
	}
}


HolyWater::~HolyWater()
{
}
