#include "HitEffect.h"



HitEffect::HitEffect()
{
	collision_able = false;
	atk_able = false;
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(39);
	this->SetAnimationSet(ani_set);
	this->vy = 0;
	this->vx = 0;
	this->x = 110;
	this->y = 330;
	timer = 0;
}

void HitEffect::Render()
{
	animation_set->at(0)->Render(x, y);

}

void HitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (Effect::getInstance()->isHitEffectActive()) {
		timer += dt;
		float X, Y;
		Effect::getInstance()->getHitEffect(X, Y);
		this->x = X;
		this->y = Y;
		if (timer > HIT_EFF_CD) {
			timer = 0;
			Effect::getInstance()->setHitEffect(false);
			Effect::getInstance()->setHitEffectPos(100, 300);
			Effect::getInstance()->getHitEffect(this->x, this->y);
		}
	}
}

void HitEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


HitEffect::~HitEffect()
{
}
