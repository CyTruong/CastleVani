#include "Ghost.h"
#include "PlayerStatus.h"


Ghost::Ghost()
{
	dirX = 0;
	dirY = 0;
	mech = GHOST_MECH_1;
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {
		if (vx == 0 && vy == 0) {
			float dis = sqrt((player->x - this->x)*(player->x - this->x) + (player->y - this->y)*(player->y - this->y));
			if (dis < 80) {
				if (player->x < this->x) {
					vx = -0.02;
				}
				else
					vx = 0.02;
			}
		}
		else {
			if (mech == GHOST_MECH_1) {
				float vexX = player->x+5 - this->x;
				float vexY = player->y+20 - this->y;
				this->dirX = (this->dirX + vexX) / 2;
				this->dirY = (this->dirY + vexY) / 2;
			}
			if (mech == GHOST_MECH_2) {
				float vexX = tempX - this->x;
				float vexY = tempY - this->y;
				this->dirX = (this->dirX + vexX) / 2;
				this->dirY = (this->dirY + vexY) / 2;
			}
			

			if (dirX > 0) {
				this->vx = GHOST_SPEED;
			}
			else {
				this->vx = -GHOST_SPEED;
			}
			this->vy = dirY * this->vx / dirX;

			if (abs(vy) > GHOST_SPEED*1.5) {
				if (vy < 0) {
					vy = -GHOST_SPEED;
				}
				if (vy > 0) {
					vy = GHOST_SPEED;
				}
			}
				
			//kiểm tra xem đến lúc đổi mech chưa
			if (mech == GHOST_MECH_1) {
				float l, t, r, b;
				player->GetBoundingBox(l, t, r, b);
				if (CheckCollisionWith(l,t,r,b)) {
					mech = GHOST_MECH_2;
					int ran = rand() % 3 - 1;
					tempX = this->x +  (20 * ran); // -20 +20 hoặc 0
					tempY = this->y - 20;
				}
			}
			if (mech == GHOST_MECH_2) {
				if (abs(this->x - tempX)<2) {
					mech = GHOST_MECH_1;
				}
			}
		}
		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}
	

}


void Ghost::Render()
{
	int ani = GHOST_ANI_LEFT;
	if (vx >= 0 ) {
		ani = GHOST_ANI_RIGHT;
	}
	animation_set->at(ani)->Render(x, y,255,!PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Ghost::clone()
{
	return nullptr;
}


Ghost::~Ghost()
{
}
