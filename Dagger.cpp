#include "Dagger.h"



Dagger::Dagger()
{
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(7);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 0;
	this->y = 0;
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	//vector<LPCOLLISIONEVENT> coEvents;
	//coEvents.clear();

	//// turn off collision when die 
	//CalcPotentialCollisions(coObjects, coEvents);
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	x += dx;
	y += dy;
	if (state== -1 || vx==0) {
		this->state = 0;
		this->vy = 0;
		this->vx = 0;
		this->x = 100;
		this->y = 800;
	}

}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_DAGGER_WIDTH;
	bottom = y + BBOX_DAGGER_HEIGHT;
}

void Dagger::Render()
{
	int ani = DAGGER_ANI_FLY_LEFT;
	if (vx>0) {
		ani = DAGGER_ANI_FLY_RIGHT;
	}
	animation_set->at(ani)->Render(x, y);
}


Dagger::~Dagger()
{
}
