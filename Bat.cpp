#include "Bat.h"



Bat::Bat()
{
	dirX = 0;
	dirY = 0;
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
	if (vx == 0 && vy == 0) {
		float dis = sqrt((player->x - this->x)*(player->x - this->x) + (player->y - this->y)*(player->y - this->y));
		if (dis < 80) {
			vx = 0.2;
		}
	}
	else {
		float vexX = player->x - this->x;
		float vexY = player->y - this->y;
		this->dirX = (this->dirX + vexX) / 2;
		this->dirY = (this->dirY + vexY) / 2;

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
		//DebugOut(L"Bat  x %f y %f \n",x,player->y);
	}
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

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
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

Enemy * Bat::clone()
{
	return nullptr;
}


Bat::~Bat()
{
}
