#include "SkeletonBone.h"
#include "PlayerStatus.h"


SkeletonBone::SkeletonBone()
{
	this->vx = 0;
	this->vy = 0;
	Hp = 1;
	state = BONE_STATE_IDLE;
	
}

void SkeletonBone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BONE_BBOX_WIDTH;
	bottom = y + BONE_BBOX_HEIGHT;
}

void SkeletonBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {
		CGameObject::Update(dt);

		if (state != -1 && vx != 0) {
			vy += 0.012f;
			x += dx;
			y += dy;
			if (this->y > 300) {
				state = OBJ_DIE;
			}

		}
		if (state == OBJ_DIE) {
			this->vy = 0;
			this->vx = 0;
			this->x = 0;
			this->y = 500;
		}
	}
	
}

void SkeletonBone::Render()
{
	animation_set->at(0)->Render(x, y, 255, !PlayerStatus::getInstance()->isZAWARUDO());

}

Enemy * SkeletonBone::clone()
{
	return nullptr;
}


SkeletonBone::~SkeletonBone()
{
}
