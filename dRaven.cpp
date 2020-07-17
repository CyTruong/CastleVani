#include "dRaven.h"
#include "PlayerStatus.h"


dRaven::dRaven()
{
	dirX = 0;
	dirY = 0;
}

void dRaven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + dRAVEN_BBOX_WIDTH;
	bottom = y + dRAVEN_BBOX_HEIGHT;
}

void dRaven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {

		if (vx == 0 && vy == 0 && dirX ==0 &&dirY ==0) {
			state = dRAVEN_STATE_IDLE;
			float dis = sqrt((player->x - this->x)*(player->x - this->x) + (player->y - this->y)*(player->y - this->y));
			if (dis < 95) {
				timer = 0;
				if (player->x < this->x) {
					vx = -0.02;
				}
				else
					vx = 0.02;
			}
		}
		else {
			timer = timer + dt;
			if (timer >1000 && timer < 1800) {
				state = dRAVEN_STATE_FLY;
				this->vx = 0;
				this->vy = 0;
			}
			else {
				if (timer > 2500) {
					timer = 0;
				}

				state = dRAVEN_STATE_FLY;

				float vexX = player->x - this->x;
				float vexY = player->y - this->y;
				this->dirX = (this->dirX + vexX) / 2;
				this->dirY = (this->dirY + vexY) / 2;

				if (dirX > 0) {
					this->vx = dRAVEN_SPEED;
				}
				else {
					this->vx = -dRAVEN_SPEED;
				}
				this->vy = dirY * this->vx / dirX;

				if (abs(vy) > dRAVEN_SPEED*1.5) {
					if (vy < 0) {
						vy = -dRAVEN_SPEED;
					}
					if (vy > 0) {
						vy = dRAVEN_SPEED;
					}
				}
			}
		
			//DebugOut(L"Bat  x %f y %f \n",x,player->y);
		}
		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}
	if (state==OBJ_DIE) {
		dirX = 0;
		dirY = 0;
	}
}

void dRaven::Render()
{
	int ani;
	if (state == dRAVEN_STATE_IDLE) {
		if (dirX<0) {
			ani = dRAVEN_ANI_IDLE_LEFT;
		}
		else {
			ani = dRAVEN_ANI_IDLE_RIGHT;
		}

	}
	if (state == dRAVEN_STATE_FLY) {
		if (dirX < 0) {
			ani = dRAVEN_ANI_FLY_LEFT;
		}
		else {
			ani = dRAVEN_ANI_FLY_RIGHT;
		}

	}
	animation_set->at(ani)->Render(x, y, 255, !PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * dRaven::clone()
{
	return nullptr;
}


dRaven::~dRaven()
{
}
