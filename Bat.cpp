#include "Bat.h"
#include "PlayerStatus.h"

# define M_PI           3.14159265358979323846
Bat::Bat()
{
	dirX = 0;
	dirY = 0;
	pVectorX = 0;
	pVectorY = 0;

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
			if (dis < 90) {
				pVectorX = player->x - this->x;
				pVectorY = player->y+10 - this->y;
				if (player->x < this->x) {
					vx = -0.02;
				}
				else
					vx = 0.02;

			}
		}
		else {

			
			

			this->dirX = (this->pVectorX + this->pVectorX) / 2;
			this->dirY = (this->pVectorY + this->pVectorY) / 2;

			if (dirX > 0) {
				this->vx = BAT_SPEED;
			}
			else {
				this->vx = -BAT_SPEED;
			}
			this->vy = dirY * this->vx / dirX;

			
		
			//DebugOut(L"Bat %d  circleY %d dir X %f dir Y %f \n",timer,circleY, dirX, dirY);
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
