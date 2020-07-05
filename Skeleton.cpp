#include "Skeleton.h"
#include "PlayerStatus.h"
#include "EnemySpawn.h"

Skeleton::Skeleton()
{
	this->vx = 0;
	this->vy = 0;
	start = false;
	dir = -1;
	Hp = 2;
	atkinterval = 1; 
	state = SKELETON_STATE_RUN;
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SKELETON_BBOX_WIDTH;
	bottom = y + SKELETON_BBOX_HEIGHT;
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {
	
		if (80 <  abs(player->x - this->x) &&  abs(player->x - this->x) < 100  	) {
			//if(atkinterval!=0)
				atkinterval += dt;
			if (atkinterval >500 && atkinterval != 0) {
				atkinterval = 0;
				ThrowBone();
			}
		}
		if (abs(player->x - this->x) <= 80) {
			if (player->x < this->x) {
				dir = 1;
			}
			if (this->x < player->x) {
				dir = -1;
			}
		}
		if (abs(player->x - this->x) >= 100) {
			if (player->x < this->x) {
				dir = -1;
			}
			if (this->x < player->x) {
				dir = 1;
			}
		}
		if (dir < 0) {
			this->vx = -SKELETON_SPEED;
		}
		if (dir > 0) {
			this->vx = SKELETON_SPEED;
		}


		//DebugOut(L"Knight dir %d \n",dir);

		// Calculate dx, dy 
		CGameObject::Update(dt);
		// Simple fall down
		vy += SKELETON_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != OBJ_DIE)
			CalcPotentialCollisions(coObjects, coEvents);



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

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;


		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Skeleton::Render()
{
	 int ani = 0;
	 if (this->x < player->x) {
		 ani = 1;
	 }
	animation_set->at(ani)->Render(x, y, 255, !PlayerStatus::getInstance()->isZAWARUDO());

}

Enemy * Skeleton::clone()
{
	return nullptr;
}

void Skeleton::ThrowBone()
{
	Enemy* bone = EnemySpawn::getInstance()->getEnemy(8, this->x, this->y);
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(33);
	bone->SetAnimationSet(ani_set);
	bone->SetPosition(this->x, this->y);
	if (this->x < player->x) {
		bone->vx = 0.09f;
	}
	else {
		bone->vx = -0.09f;
	}
	bone->vy = -0.25f;
	bone->state = 0;
}


Skeleton::~Skeleton()
{

}
