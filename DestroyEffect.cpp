#include "DestroyEffect.h"



DestroyEffect::DestroyEffect()
{
	collision_able = false;
	atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(40);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 110;
	this->y = 330;
}

void DestroyEffect::Render()
{
	bool isdesactive = Effect::getInstance()->isDesEffectActive();
	bool endani = animation_set->at(0)->Render(x, y,255, isdesactive);
	if (endani) {
		Effect::getInstance()->setDesEffect(false);
		Effect::getInstance()->setDesEffect(100, 300);
	}
}

void DestroyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Effect::getInstance()->getDesEffect(this->x, this->y);

}

void DestroyEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


DestroyEffect::~DestroyEffect()
{
}
