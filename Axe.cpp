#include "Axe.h"
#include "Utils.h"


Axe::Axe()
{
	this->atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(11);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 0;
	this->y = 500;
	this->state = AXE_STATE_IDLE;
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BBOX_AXE_WIDTH;
	bottom = y + BBOX_AXE_HEIGHT;
}
void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (state != -1 && vx != 0) {
		vy += 0.012f;
		x += dx;
		y += dy;
	}
	if (state==-1) {
		this->vy = 0;
		this->vx = 0;
		this->x = 0;
		this->y = 500;
		this->state = AXE_STATE_IDLE;
	}

}

void Axe::Render()
{
	animation_set->at(0)->Render(x, y);
}


Axe::~Axe()
{
}
