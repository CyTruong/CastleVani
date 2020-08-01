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
	allowjump = false;
	jumping = false;
	state = SKELETON_STATE_RUN;
	isblocked = false;
	havebrick = true;
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
	
		if (abs(player->x - this->x) < 150 && !start) {
			start = true;
			state = SKELETON_STATE_RUN;
		
		}
		if (start) {
			if (/*80 <  abs(player->x - this->x) &&*/  abs(player->x - this->x) < 100) {
				//if(atkinterval!=0)
				atkinterval += dt;
				if (atkinterval > ATK_CD && atkinterval != 0) {
					atkinterval = 0;
					ThrowBone();
				}
			}
			
			
			if (dir < 0) {
				this->vx = -SKELETON_SPEED;
			}
			if (dir > 0) {
				this->vx = SKELETON_SPEED;
			}
			if (isblocked) {
				dir = -dir;
				allowjump = true;
				vy = SKELETON_JUMP_SPEED;
			}
			if (allowjump) {
				allowjump = false;
				jumping = true;
				this->vy = -SKELETON_JUMP_SPEED;
			}
			else {
				
			}

			//DebugOut(L"Knight dir %d \n",dir);

			// Calculate dx, dy 
			// Simple fall down
			vy += SKELETON_GRAVITY * dt;

			CGameObject::Update(dt);

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			if (state != OBJ_DIE)
				CalcPotentialCollisions(coObjects, coEvents, true,true);


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

				if ((rdy < 0 && rdx == 0 )  || (rdy == 0 && rdx > 0)) {
					x += vx * dt;
					y += vy * dt;
				}
				else {
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;

					allowjump = false;
					jumping = false;
					isblocked = false;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;


					if (!isblocked &&havebrick) {
						if (abs(player->x - this->x) <= 70) {
							if (player->x < this->x) {
								dir = 1;
							}
							if (this->x < player->x) {
								dir = -1;
							}
						}
						if (abs(player->x - this->x) >= 110) {
							if (player->x < this->x) {
								dir = -1;
							}
							if (this->x < player->x) {
								dir = 1;
							}
						}
					}
				}
			
			}

			//Chống lọt hố
			float pointX = 0;
			float pointY = y + SKELETON_BBOX_HEIGHT + 5;
			if (dir < 0) {
				pointX = this->x - 5;
			}
			else
				if (dir >= 0) {
					pointX = this->x + SKELETON_BBOX_WIDTH/2 + 5;
				}
			bool havebrick = false;
			isblocked = false;
			if (!isblocked) {
				for (int i = 0; i < coObjects->size(); i++) {
					LPGAMEOBJECT obj = coObjects->at(i);
					if (obj->x < pointX && pointX < obj->x + 16) {
						if (obj->y < pointY && pointY < obj->y + 16) {
							havebrick = true;
							break;
						}
					}

				}
			}
			

			//Chống stuck
			if (!isblocked) {
				pointY = y + SKELETON_BBOX_HEIGHT - 5;
				isblocked = false;
				for (int i = 0; i < coObjects->size(); i++) {
					LPGAMEOBJECT obj = coObjects->at(i);
					if (obj->x < pointX && pointX < obj->x + 16) {
						if (obj->y < pointY && pointY < obj->y + 16) {
							isblocked = true;
							break;
						}
					}

				}
			}
			
			if (isblocked && !allowjump && !jumping) {
				DebugOut(L"Brick vl  , xương nhảy lên %d \n", dt);
				allowjump = false;
			}
			if ((!havebrick ) && !allowjump && !jumping) {
				DebugOut(L"Chống lọt hố , xương nhảy lên %d \n", dt);
				allowjump = true;

			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}	
	}
	//DebugOut(L"skeleton x y %f %f \n", x, y);

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
