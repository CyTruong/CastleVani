#include "Bat.h"
#include "PlayerStatus.h"

# define M_PI           3.14159265358979323846
Bat::Bat()
{
	dirX = 0;
	dirY = 0;
	pVectorX = 0;
	pVectorY = 0;
	circleY = 0;
	timer = 0;
	Y_down = true;
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {
		if (pVectorX == 0 && pVectorY == 0) {
			float dis = sqrt((player->x - this->x)*(player->x - this->x) + (player->y - this->y)*(player->y - this->y));
			if (dis < 80) {
				pVectorX = player->x - this->x;
				pVectorY = player->y+10 - this->y;
				if (player->x < this->x) {
					vx = -0.02;
				}
				else
					vx = 0.02;

				timer = 1600;
			}
		}
		else {

			timer = timer + dt;
			if (timer > 200) {
				timer = 0;
				if (Y_down) {
					circleY = circleY + 30;
					if (circleY >= 90) {
						Y_down = false;
					}
				}
				else {
					circleY = circleY - 30;
					if (circleY <= -90) {
						Y_down = true;
					}
				}
				DebugOut(L"new ydown %d ", circleY);
			}

			

			this->dirX = (this->pVectorX + this->pVectorX) / 2;
			this->dirY = (this->pVectorY + this->pVectorY) / 2;

			if (dirX > 0) {
				this->vx = BAT_SPEED;
			}
			else {
				this->vx = -BAT_SPEED;
			}
			this->vy = dirY * this->vx / dirX;

			if (abs(vy) > BAT_SPEED*1.5) {
				if (vy < 0) {
					vy = -BAT_SPEED;
				}
				if (vy > 0) {
					vy = BAT_SPEED;
				}
			}
			if (Y_down == 1) {
				vy +=  BAT_SPEED*1.2;
			}
			else
			{
				vy -=   BAT_SPEED*1.2;
			}
			DebugOut(L"Bat %d  circleY %d dir X %f dir Y %f \n",timer,circleY, dirX, dirY);
		}
		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}
	

}

void Bat::Render()
{
	int ani = 0;

	if (vx < 0) {
		ani = BAT_ANI_LEFT;
	}
	if (vx > 0 )
	{
		ani = BAT_ANI_RIGHT;
	}
	if (vx = 0) {
		ani = BAT_ANI_IDLE;
	}
	animation_set->at(ani)->Render(x, y,255,!PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Bat::clone()
{
	return nullptr;
}


Bat::~Bat()
{
}
